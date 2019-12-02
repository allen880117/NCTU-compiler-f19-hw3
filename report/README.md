# 作業 3 報告
> 學生：王祥任
>
> 學號：0616309
___
## 功能
#### 編譯
* `cd src && make clean && make`
* 由於本次採用`C++`撰寫，所以必須修改`Makerfile`以支援編譯。

#### 測試
* `cd test && python3 test.py`

#### 使用Parser 且 Dump AST
* `cd src && ./parser <file_name.p> --dump-ast`
___
## `Parser.y`的主要修改
#### 增加更多標頭檔和 AST 的 Root
* 在 C Declarationh Area 新增所有 Node 的標頭檔。
    ```cpp
    %{
    #include "include/AST/ast.hpp"
    #include "include/AST/program.hpp"
    #include "include/AST/declaration.hpp"
    #include "include/AST/variable.hpp"
    #include "include/AST/constant_value.hpp"
    ...
    #include "include/visitor/visitor.hpp"
    #include "include/core/error.h"
    ...
    %}
    ```
* 在 C Declaration Area 新增 AST Node 的 Root 。
    ```cpp
    %{
    ...
    static Node AST;
    %}
    ```

* 在 Declaration Area 新增要求`Parser.cpp`加入的標頭檔。
    ```cpp
    %{
    ...
    %}
    %code requires { #include "include/AST/ast.hpp" }
    %code requires { #include "include/AST/program.hpp" }
    %code requires { #include "include/AST/declaration.hpp" }
    ...
    %code requires { #include "include/visitor/visitor.hpp" }
    ...
    ```
    
#### 增加型別描述
* 在 C Declaration Area 新增一些型別用於`%union`中。
    ```cpp
    %{
    ...
    // 用於 IdList 的紀錄
    // 負責紀錄各 identifer 的名稱和位置
    struct id_info{
        string name;
        uint32_t line_number;
        uint32_t col_number;
    };
    
    // 用於 FormalArgs 的建立和紀錄回傳
    struct NodeWithTypeList{
        Node node;            // 特指 Declaration Node // 下方介紹
        VariableInfo* type;   // 下方介紹
        uint counter;         // 紀錄有多少個 Id 為此型別的參數
    };
    ...
    %}
    ```
    
* 在 Declaration Area 新增 `%union` 以增加 scanner (`yylval`)的可回傳型別 
    ```cpp
    %union {
        int    val;   // 整數值
        double dval;  // 浮點數值
        char*  text;  // 字串

        enum enumOperator op_type; // 運算符

        Node      node;            // class ASTNodeBase*    // 下方介紹
        NodeList* node_list_ptr;   // vector<ASTNodeBase*>* // 下方介紹

        struct NodeWithTypeList*           node_w_type_list_ptr;
        struct vector<NodeWithTypeList*>*  node_w_type_list_ptr_list_ptr;

        vector<struct id_info>* id_list_ptr;
        VariableInfo*           variable_info_ptr;
    }
    ```

* 在 Declaration Area 為某些 Non-terminal 和 terminal 添加其回傳型別
    ```cpp
        /* Operator */
    %token <op_type> ASSIGN
    %left <op_type> OR
    ...
    %left <op_type> PLUS MINUS
    %left <op_type> MULTIPLY DIVIDE MOD
    
    ...
        /* Identifier */
    %token <text> ID

        /* Literal */
    %token <val> INT_LITERAL
    %token <dval> REAL_LITERAL
    %token <text> STRING_LITERAL

        /* Type of Nonterminals */
    %type <text> ProgramName
    %type <text> FunctionName

    %type <node> Declaration
    %type <node_list_ptr> Declarations
    %type <node_list_ptr> DeclarationList
    ...

    %type <node_w_type_list_ptr> FormalArg
    %type <node_w_type_list_ptr_list_ptr> FormalArgs
    %type <node_w_type_list_ptr_list_ptr> FormalArgList

    ...

    %type <id_list_ptr> IdList
    %type <variable_info_ptr> ReturnType
    ...
    %type <variable_info_ptr> LiteralConstant    
    ```

#### 添加 Action 至每一個 Grammer Rule
* 以 Program 為例：
    ```cpp
    Program:
        ProgramName SEMICOLON DeclarationList FunctionList CompoundStatement
        END ProgramName {
            // Program Node (Also root Node)
            string return_type = "void";
                                            // 建立 ProgramNode 為 AST Root
            AST = new ProgramNode(          // 建立一 ProgramNode
                @1.first_line,              // Program Name 的位置 (整數)
                @1.first_column,            // Program Name 的位置 (整數)
                $1,                         // Program Name (字串)
                return_type,                // 回傳型態 (此處為字串)
                $3,                         // Declaration List (NodeList*)
                $4,                         // Function List (NodeList*)
                $5,                         // Compound Statement (Node)
                @7.first_line,              // End Program Name 的位置 (整數)
                @7.first_column,            // End Program Name 的位置 (整數)
                $7                          // End Program Name (字串)
            );
        }
    ;

    ProgramName:
        ID{
            $$ = $1; // ProgramName 的回傳值為 ID 的值 (From Scanner)
        }
    ;
    ```

* 以此類推，完善並建構整個`AST`。

#### 增加 Traverse AST 的選項
* 增加`--dump-ast`，若添加此參數，則輸出 Inorder Traverse AST 的結果。

    ```cpp
    void dumpAST(ASTNodeBase* node){
        ASTVisitor visitor;
        node->accept(visitor);
    }
    ```
___
## `Scanner.l`的主要修改
#### 增加回傳值

___

## `AST`的功能
#### 紀錄程式整體結構
___
## `AST`的建構
* 依照 [Abstract Syntactic Definitions](https://github.com/compiler-f19/hw3-allen880117/blob/master/ast_guideline.md) 實作。
* 為方便資訊的擷取和建構，定義了某些型別，將在下方介紹。

#### ASTNodeBase
* 在 AST 中最基本的型別，每一個 Node 皆繼承自此型別。
* 具有一虛擬函數為和 ASTVistorBase 的接口。

#### Node
```
class ASTNodeBase*
```
* 即 ASTNodeBase 的指標型別。
* 是在建構 AST 中互相傳遞 Node 使用的型別。
* 採用指標型別的好處之一為空指標的傳入，可以表明在 AST 中無此子點存在。
    > zero or one

* 以 ProgramNode 為例：
    ```cpp
    class ProgramNode : public ASTNodeBase
    {
        public:
            ...
            NodeList* declaration_node_list; // zero or more
            NodeList* function_node_list; // zero or more
            Node compound_statement_node;
            ...

        public:
            ... 
            void accept(ASTVisitorBase &v) {v.visit(this); }
            void print();
    };
    ```
    compound_statement_node 就是以 Node 型別紀錄於 ProgramNode 中。
  
#### NodeList 和 NodeList*
```
vector< class ASTNodeBase* >
vector< class ASTNodeBase* >*
```
* 即 Node 的 vector，和其指標型別。
* NodeList 用意為放置一連串 Node。
* 實際上在傳遞資訊時，以 NodeList* 型別使用居多。
* 採用指標型別的好處之一為空指標的傳入，可以表明在 AST 中無此存在。
    > zero or more

* 以 ProgramNode 為例：
    ```cpp
    class ProgramNode : public ASTNodeBase
    {
        public:
            ...
            NodeList* declaration_node_list; // zero or more
            NodeList* function_node_list; // zero or more
            Node compound_statement_node;
            ...

        public:
            ... 
            void accept(ASTVisitorBase &v) {v.visit(this); }
            void print();
    };
    ```
    declaration_node_list 就是以 NodeList* 型別紀錄於 ProgramNode 中。
    
#### VariableInfo
```cpp
typedef struct __VariableInfo{ 

    enumTypeSet type_set;
    enumType type;
    
    vector<IntPair> array_range;
    
    int int_literal;
    double real_literal;
    string string_literal;
    BooleanLiteral boolean_literal;

} VariableInfo ;
```
* 此型別負責紀錄變數、常數或型別等資訊。
* 用在回傳值型別、變數型別、常數型別等方面。
* 此型別負責的資訊紀錄較多，以下逐一介紹。
    * ```cpp
      enum enumTypeSet{
          SET_SCALAR = 300,
          SET_ACCUMLATED,
          SET_CONSTANT_LITERAL,
          UNKNOWN_SET
      };
      ```
    此變數或常數的型別群。
    有`SCALAR`、`ACCUMLATED`、`CONSTANT`、`UNKNOWN`等。
    
    * ```cpp
      enum enumType{
          TYPE_INTEGER = 400,
          TYPE_REAL,
          TYPE_STRING,
          TYPE_BOOLEAN,
          TYPE_VOID,
          UNKNOWN_TYPE
      };
      ```
    此變數或常數的(單位元素)型別。
    有`INTEGER`、`REAL`、`STRING`、`BOOLEAN`、`VOID`、`UNKNOWN`等。
    
    * ```cpp
      typedef struct __IntPair{
          int start;
          int end;
      } IntPair;
      vector<IntPair> array_range;
      ```
    負責紀錄一維或多維陣列的範圍。
    
    * ```cpp
      int int_literal;
      double real_literal;
      string string_literal;
      BooleanLiteral boolean_literal;
      ```
    負責紀錄四種常數的值。

* 在建構 AST Node 時，此型別的資訊通常會依照以下流程轉換：
    1. 根據 enumTypeSet 判斷其隸屬群為純量、陣列、常數、不明等。
    2. 根據 enumType：
        * 如果為純量群，則即為其型別
        * 如果為陣列群，則即為其單位元素的型別
        * 如果為常數群，則即為其常數的型別
    3. 假設其為陣列群，則可從 array_range 取得維度的資訊。
    4. 假設其為常數群，則可從 literal 中取得相對應型別的常數值。
    
## `Visitor Pattern` 的建構
* 當我們建構完 AST 後，我們便可以以某些方式遍歷所有的 Node。