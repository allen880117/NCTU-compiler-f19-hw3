# AST & Visitor Pattern

**實際範例**

我們在 `example/` 資料夾內放了一個簡單的範例，同學可以直接使用 `make` 來進行編譯並執行。裡面有不少實踐細節供同學參考。

## 有關 AST 的小小廢話

hw2 執行 yacc 時會覺得程式好像穿梭在一個樹狀結構之中，但一跑完 yacc parsing 程序後，這個假想的樹狀結構就會消失，沒辦法再後續利用。所以 Parsing 時的重點之一是建立一個架構上完全相同的資料結構，供後續程式分析，也就是 AST。而 AST 上每個節點的實際型別都不相同，這會讓未來在進行語法檢查時的樹走訪遇上一些困難 - 必須要判斷是哪種型別的資料。

### **AST Traversal**

在實踐上我們推薦兩種做法，且在語言上的選擇也會分別使用 C 或 C++ 實踐，你可以選取任何你想要的方式撰寫。在這裡只提供一些參考與實用建議。

+ C

  `struct` 中包含一個 `enum` 以及一個 `union`，`union` 裡包含不同種節點的屬性資料。在走訪時使用 `switch ... case` 判斷 `enum` 所代表的種類，來使用特定的 `union` 成員並做出不同行為。

+ C++

  如果還想使用 C++ 的物件導向寫法，可以先創一個屬於 AST node 的 base class，再繼承衍生出其他 node 類別。在走訪時利用語言內建的多型(Polymorphism)機制，根據不同節點類別做出不同行為。
  如果你有考慮使用多型的話，可以採用後續提到的 Visitor Pattern 撰寫這次作業，我們也有附上 Visitor Pattern 的寫法。

## Visitor Pattern

Visitor Pattern 是一種 **設計模式** (Design Pattern)，但其實不用很懂設計模式也可以使用 Visitor Pattern。在這裡會進一步解釋為什麼會推薦各位使用，還有為什麼你該學習這個 Pattern。

> :raised_hand: 在這之後的文章會把 Visitor Pattern 簡寫為 `VP`

先秀 code 吧!

**Visitor Pattern初探**

在撰寫 visitor class 時，通常會 overload 出一堆名為 `visit` 的函式，根據不同的參數型別而有不同的行為。
以底下的 `LunchVisitor` 為例，我們想要一個專門吃午餐的 class，所以這個 class 就因針對吃午餐而命名為 `LunchVisitor`，而它的實際實踐內容就只有根據不同食物類別而有相對應的行為而已。

```cpp
class LunchVisitor : public FoodVisitorBase {
public:
  void visit(Pepsi *m) override { m->drink(); }
  void visit(HotDog *m) override {
    if (!m->chilipower.exists()) {
      cout << "Serious ?" << endl;
    }
    m->eat();
  }
  void visit(GoldenArches *m) override {
    if (m->item.BigMac.price > 10) {
      cout << "Nah." << endl;
      goToBurgerQueen();
    }
    m->order("BigMac");
    m->eatAll();
    m->cleanTable();
  }
};
```

在資料結構設計上，`Pepsi`、 `HotDog`、`GoldenArches` 皆繼承自 `FoodBase` 類別，而 `LunchVisitor` 所繼承的 `FoodVisitorBase` 也是針對 `FoodBase` 撰寫。我們的 `LunchVisitor` 已經針對了不同類別撰寫行為，接下來的問題則會是怎麼將這個類別傳給這個 visitor ?

可以先思考一下食用情境：

實際上，我們會用 `std::vector` 裝入一堆 `FoodBase` 衍生類別所建構的物件。想把食物吃光光的話，就要使用一個迴圈走訪這個容器，在這同時我們會對每個食物傳入我們的 visitor。

有了 visitor 的 `visit` 介面後，我們需要讓目標資料結構想辦法使用到 visitor 裡面各個 overloading 的 `visit` 方法(函式)。但因為 vector 中的元素型別是 `FoodBase *`，因此 visitor 無法正確判別該使用哪個 `visit` 方法。所以我們採用 `this` 指標與 C++ 的 `virtual method` 來獲得實際的物件型別。

所以每個繼承 `FoodBase` 的類別都要實踐一個 `accept` 的 `virtual function`。 再讓 C++ 編譯器在走訪這個 `vector<FoodBase*>` 時正確選擇並呼叫出衍生類別實作的 `accept` 函式。

> 更多有關 `virtual function` 可以參考 [Virtual Function in C++](https://www.geeksforgeeks.org/virtual-function-cpp/)。

以 `Pepsi` 為例：

```cpp
class Pepsi : public FoodBase {
public:
  void accept(FoodVisitorBase &v) {
    v.visit(this); // v.visit(Pepsi *)
  }
  void drink();
};
```

最後，我們的食用場景會是：

```cpp
DiningTable table; // std::vector<FoodBase *>
LunchVisitor lv;
vector<FoodBase *>::iterator iter;
for (iter = table.begin(); iter != table.end(); iter++) {
  (*iter)->accept(lv);
}
```

**為什麼要嘗試使用 Visitor Pattern**

進入正題，在先前的建立 AST 中，我們期望同學會對 AST 的子節點建立一個基礎型別，再根據不同 language construct 繼承出不同的節點型別。完成之後，同學只需要走訪 AST 並 dump 出每個節點的內容就完成這次作業了。好，所以看起來根本不需要什麼 Visitor Pattern 的存在就能完成 hw3 了吧。

動用 `Visitor Pattern` 秀出整個 AST 算不算是種 over-engineering？

如果目標只是要秀出 AST ，是的，根本不需要使用到 `VP`。但回到整學期的目標 - **撰寫編譯器** 來看，在 dump AST 後，hw4, hw5 需要會需要根據 AST 做進一步的操作，比如說語意檢查、產生 `function call`，`register allocation` 等等對應的機器碼。這時候 `VP` 的重要性就開始顯現了。

先思考一下在擁有 AST 後你會如何撰寫後續編譯流程，單看這學期要做的語意檢查，同學就需要確認 `函式回傳型別`，`陣列下標型別限制`，`運算子型別限制`，`重複宣告變數` 等等問題，沒有意外肯定是寫上一些新函式來分別支援作業要求，但這些函式寫好之後會放在哪裡，又或是說**該如何管理**它們？最直觀來看，肯定是`寫成不同 AST 節點型別的 member function`。
這種方式的最大缺點是，每當新增一個功能時，就會在所有 AST 節點的型別上安插一些新函式，當編譯器慢慢開發完整後，每個節點上都會存在**一大堆彼此不相干的函式**，每次開發時都要自行理解這些函式彼此間的關係。這是個很大的管理成本，甚至會大大降低整個編譯器專案的可維護性。

這就是 `Visitor Pattern` 適用在這裡的原因 - 走訪相同的資料結構，但在這個結構(AST) 上一次次做出不同的運算。透過 `VP` 你只需要針對每個步驟做出對應的 `visitor` class，相關演算法都透過不同的 `visit` 函式來實踐。
編譯中的每一種檢查，每一次最佳化都寫成一個獨立的 `visitor` class，把邏輯上相關的函式集中管理。AST Node 從此只負責最基本的資料結構功能，演算法部分全部交由 `visitor` 管理。

當然，`Visitor Pattern` 也不是毫無缺點。考慮這個情況：

> --- [簡答題] 一題10分 ---
>
> > `編義氣` 是個鑽研編譯器多年的勇者，最近十年來他潛心開發一個偉大的編譯器 **LCC** - Life Companion Compiler(人生伴侶編譯器)：只需要描述另一半的特質，`LCC` 就可以編譯出一個針對用戶要求的完美另一半。在寫好 5000 多個進行最佳化分析的 visitor class 之後... 完了，他發現他描述另一半的語法樹節點型別就獨獨缺了 `腦子`。
> >
> > `編義氣` 是個真實的人，絕不能容許另一半沒腦子，但也不能接受自己沒有另一半，只好認份的補上有關 `腦子` 的所有 visit member functions。
>
> ~試問：各位同學 hw3 能拿幾分？~

回到 `LCC` 的狀況，在寫好一堆 `visitor` class 之後如果想要新增新的節點，就會是噩夢的開始。使用者必須要在自己寫的所有 `visitor` class 中一一支援`腦子`型別。在一個有 5000 個 `visitor` class 的專案上支援一個新型別，就要再寫 5000 個函式。

但編譯器這門課不會有這個問題，原因很簡單：因為*~~各位同學都不需要 LCC 就能找到自己的另一半~~*我們的節點型別在作業三之後就不會再新增了。這種情況之下，使用 `Visitor Pattern` 基本上不會遇到缺點。

再告訴各位同學一點，現今的編譯器實作也大多採用 `Visitor Pattern`。也可以說這是在撰寫編譯器上一個非常經典的設計模式，學會這個之後你的專案就更接近現實世界了一些。 還有未來如果提供 sample code 或是有考試的話，也都預設同學已經學會 `VP` 了哦 :heart:。