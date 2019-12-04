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
* 在 C Declaration Area 新增定義 yyltype ，以記錄從 scanner 傳來的位置資訊。
    ```cpp
    #define YYLTYPE yyltype

    typedef struct YYLTYPE {
        uint32_t first_line;
        uint32_t first_column;
        uint32_t last_line;
        uint32_t last_column;
    } yyltype;
    ```
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
* 增加`--dump-ast`，若在執行時添加此參數，則輸出 Inorder Traverse AST 的結果。

    ```cpp
    void dumpAST(ASTNodeBase* node){
        ASTVisitor visitor;
        node->accept(visitor);
    }
    ```
___
## `Scanner.l`的主要修改
#### 增加回傳值
* 利用 yylval 結構內的變數回傳 token 相應的值。
* 會使用在 scanner.l 中者為以下顯示的四種。
```cpp
%union {
    int    val;    // 整數值
    double dval;   // 浮點數值
    char*  text;   // 字串值

    enum enumOperator op_type; // 專司Operator種類的回傳

    ...
}
```

* 以 yylval.op_type 紀錄並利用 enum 回傳 operator 的種類。
```cpp
    /* Operator */
"+"   { TOKEN_CHAR('+'); yylval.op_type=OP_PLUS;            return PLUS;}
"-"   { TOKEN_CHAR('-'); yylval.op_type=OP_MINUS;           return MINUS;}
"*"   { TOKEN_CHAR('*'); yylval.op_type=OP_MULTIPLY;        return MULTIPLY;}
"/"   { TOKEN_CHAR('/'); yylval.op_type=OP_DIVIDE;          return DIVIDE;}
"mod" { TOKEN(mod);      yylval.op_type=OP_MOD;             return MOD;}
":="  { TOKEN(:=);       yylval.op_type=OP_ASSIGN;          return ASSIGN;}
"<"   { TOKEN_CHAR('<'); yylval.op_type=OP_LESS;            return LESS;}
"<="  { TOKEN(<=);       yylval.op_type=OP_LESS_OR_EQUAL;   return LESS_OR_EQUAL;}
"<>"  { TOKEN(<>);       yylval.op_type=OP_NOT_EQUAL;       return NOT_EQUAL;}
">="  { TOKEN(>=);       yylval.op_type=OP_GREATER_OR_EQUAL;return GREATER_OR_EQUAL;}
">"   { TOKEN_CHAR('>'); yylval.op_type=OP_GREATER;         return GREATER;}
"="   { TOKEN_CHAR('='); yylval.op_type=OP_EQUAL;           return EQUAL;}
"and" { TOKEN(and);      yylval.op_type=OP_AND;             return AND;}
"or"  { TOKEN(or);       yylval.op_type=OP_OR;              return OR;}
"not" { TOKEN(not);      yylval.op_type=OP_NOT;             return NOT;}
```

* 以 yylval.text 紀錄 Identifier 的名稱。 
```cpp
    /* Identifier */
[a-zA-Z][a-zA-Z0-9]* { ...; yylval.text = strdup(yytext); return ID; }
```

* 以 yylval.val 紀錄整數值(全部轉為十進位)。
```cpp
    /* Integer (decimal/octal) */
{integer} { ...; yylval.val = atoi(yytext); return INT_LITERAL; }
0[0-7]+   { ...; yylval.val = strtol(yytext, NULL, 8); return INT_LITERAL; }
```

* 以 yylval.dval 紀錄浮點數值(科學記號轉為純浮點數)。
```cpp
    /* Floating-Point */
{float} { ...; yylval.dval = atof(yytext); return REAL_LITERAL; }

    /* Scientific Notation [Ee][+-]?[0-9]+ */
({integer}|{float})[Ee][+-]?({integer}) {
    TOKEN_STRING(scientific, yytext);
    yylval.dval = atof(yytext);
    return REAL_LITERAL;
}
```

* 以 yylval.text 紀錄字串值。
```cpp
    /* String */
\"([^"\n]|\"\")*\" {
    ...
    yylval.text = strdup(yytext);
    return STRING_LITERAL;
}
```
___

## `AST`的功能
#### 紀錄程式整體結構

* 藉由建構AST，我們可以在Parser完成其任務後得到一詳細的程式架構圖。
* AST可以充分表達程式的結構，在之後建立`Symbol Table`等實作上將會十分有用處。
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
#### NodeWithTypeList 和 vector<NodeWithTypeList*>*
```cpp
    struct NodeWithTypeList{
        Node node;            // 特指 Declaration Node // 下方介紹
        VariableInfo* type;   // 下方介紹
        uint counter;         // 紀錄有多少個 Id 為此型別的參數
    };
    ...
    %}
```
* 用於 FormalArgList 的建立和紀錄回傳

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
    `enumTypeSet` 負責此變數或常數的型別群。
    有`SCALAR`、`ACCUMLATED`、`CONSTANT_LITERAL`、`UNKNOWN`等。
    
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
    `enumType` 負責枚舉此變數或常數的(單位元素)型別。
    有`INTEGER`、`REAL`、`STRING`、`BOOLEAN`、`VOID`、`UNKNOWN`等。
    
    * ```cpp
      typedef struct __IntPair{
          int start;
          int end;
      } IntPair;

      vector<IntPair> array_range;
      ```
    `vector<IntPair>` 負責紀錄一維或多維陣列的範圍。
    
    * ```cpp
      int int_literal;
      double real_literal;
      string string_literal;
      BooleanLiteral boolean_literal;
      ```
    以上負責紀錄四種常數的值。

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
* 若採用 Vistior Pattern 的設計，程式的呼叫上大致如下流程：
    1. Node accept Visitor。
    2. 呼叫 Node 的 Visit-Function (in Visitor)。
    3. Visit-Function 裡面已經定義好該如何去 "Visit" 這個 Node。

* 而在每一個 Node 中都有繼承自 ASTNodeBase 的 accept() 並對其多載。
* 同時每一個 Node 中都有各自獨立的 print() 或是其餘函數。
```cpp
class ProgramNode : public ASTNodeBase
{
    ...
        void accept(ASTVisitorBase &v) {v.visit(this); }
        void print();
};
```

* 採用多型和虛擬函數的方式，可以大量撰寫各 Node 的 Visit-Function。
```cpp
class ASTVisitor : public ASTVisitorBase
{
    public:
        void visit(class ProgramNode *m) override;
        void visit(class DeclarationNode *m) override;
        void visit(class VariableNode *m) override;
        void visit(class ConstantValueNode *m) override;
        void visit(class FunctionNode *m) override;
        void visit(class CompoundStatementNode *m) override;
        void visit(class AssignmentNode *m) override;
        void visit(class PrintNode *m) override;
        void visit(class ReadNode *m) override;
        void visit(class VariableReferenceNode *m) override;
        void visit(class BinaryOperatorNode *m) override;
        void visit(class UnaryOperatorNode *m) override;
        void visit(class IfNode *m) override;
        void visit(class WhileNode *m) override;
        void visit(class ForNode *m) override;
        void visit(class ReturnNode *m) override;
        void visit(class FunctionCallNode *m) override;
};
```

* 而 Visit-Function 大致以如下形式撰寫。
* 基本上 Node A 是不會直接呼叫 Node B 的 print()。
* 因為每個 Node 都有在Traverse上都有不同的細節需要注意。  
```cpp
void ASTVisitor::visit(ProgramNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->declaration_node_list != nullptr)
            for(uint i=0; i< m->declaration_node_list->size(); i++){
                (*(m->declaration_node_list))[i]->accept(*this);
            }

        if (m->function_node_list != nullptr)
            for(uint i=0; i< m->function_node_list->size(); i++){
                (*(m->function_node_list))[i]->accept(*this);
            }

        if (m->compound_statement_node != nullptr)
            m->compound_statement_node->accept(*this);
    this->space_counter_decrease();
}
```

## [BONUS] HW3 Spec 可以改進的地方
### 前言
* 先說一聲辛苦助教們了。
* 我是覺得這次的 Spec 其實完成度已經很高了。
    ```
    真的很高!
    你各位知道有個漂亮的Spec是多麼幸福的一件事嗎!
    我看到每一個 Node 都有明確定義的時候真的是嗨到不行!
    ```
* **`所以接下來這個部分有點像是雞蛋裡挑骨頭，還請見諒。`**

### BUG & Spec 的細節疑問
* 這是我之前找到的[Bug](https://github.com/compiler-f19/Discussion/issues/55)，已經發在Discussion裡面且被標上`Solved`了。
* 這我不確定是不是[Bug](https://github.com/compiler-f19/Discussion/issues/53)，應該比較像是 Spec 在說明上稍微不清楚，同樣已經發在Discussion裡面且被標上`Solved`了。

### 可能可以改進的細節
* 這是以我自己實作的經驗回推的。
* 我基本上是 Spec 和 yacc 講義全部看個兩、三遍，就開始做了。
* 遇上問題就靠 Console 噴的訊息和 Google 去 Debug。
* 有實作細節上的疑問才會上 Discussion 發 Issue。
* 而剛開始做的時候其實會有一些不確定的地方，以下就一一寫出來。

#### 1. 該用純`C`還是混`C++`
* Repository 最初的檔案是以 `C` 的語法撰寫。
* 但由於 Spec 裡面有說比較推薦使用 `C++` ，且尚須實作`Visitor Pattern`，而`VP`的解說是以`C++`為範例說明，所以可能會在使用純`C` 還是混`C++`間猶豫。
* 我有發一個 [Issue](https://github.com/compiler-f19/Discussion/issues/52) 來確認想法後才開始實作。

#### 2. 在 yacc/bison 使用 `C++`
* 主要的問題是能在 `%union` 中放置的型別。
* 由於 `yacc` 的講義中只解說了 `C` 的部分，所以 `C++` 的使用上要稍微摸索一下。
* 參考[這份資料](https://www.gnu.org/software/bison/manual/html_node/C_002b_002b-Unions.html)，我們可以知道非 [`POD (Plain Old Data)`](https://zh.wikipedia.org/wiki/POD_(%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1)) 的型別是不能使用在 `%union` 中的。

### 感謝助教的SPEC那超高的完成度，辛苦了。