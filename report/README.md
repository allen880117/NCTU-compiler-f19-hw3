# 作業 3 報告
> 學生：王祥任
>
> 學號：0616309
___
## 功能

## `Parser.y`的主要修改
### 增加更多標頭檔

## `Scanner.l`的主要修改
### 增加回傳值

## `AST`的功能
### 紀錄程式整體結構

## `AST`的建構
* 依照 [Abstract Syntactic Definitions](https://github.com/compiler-f19/hw3-allen880117/blob/master/ast_guideline.md) 實作。
* 為方便資訊的擷取和建構，定義了某些自定義型別，將在下方介紹。

### ASTNodeBase
* 在 AST 中最基本的型別，每一個 Node 皆繼承自此型別。
* 具有一虛擬函數為和 ASTVistorBase 的接口。

### Node
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
  
### NodeList 和 NodeList*
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
    
### VariableInfo
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
* 