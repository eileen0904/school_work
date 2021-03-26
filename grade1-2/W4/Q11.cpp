/*請設計一個類別 bar3d 代表一個長方體，該類別中要有公開的資料成員 width，height 跟 depth 分別代表寬，長跟高。
width，height 跟 depth 是 float 型態的資料成員。
請設計一個建構子給 bar3d 這類別，該建構子以三個浮點數為參數，依序用來設定 width，height 跟 depth。
width，height 跟 depth 的有效範圍是零到一千，如果有任何一個屬性不在範圍內，就將三個屬性都設成零。
請設計一個預設建構子給 bar3d 類別，該建構子沒有參數，會將 width，height 跟 depth 都設為 0。
請給 bar3d 一個函數成員 getVolume ，該函數沒有參數，會回傳一個浮點數型態的值表示體積。
請設計一個函數成員 scale ，該函數有一個 float 型態的參數，會以該參數為比例改變 bar3d 的 width ， height 跟 depth 。
請設計一個函數成員 addVolume ，該函數有一個 bar3d 型態的參數，會將兩個 bar3d 的體積加總後回傳，其回傳直為浮點數。*/


class bar3d
{
public:
    float width;
    float height;
    float depth;
  	bar3d(){
  		width = 0;
  		height = 0;
  		depth = 0;
	}
    bar3d(float a, float b, float c){
        if((a<=1000 && a>=0) && (b<=1000 && b>=0) && (c<=1000 && c>=0)){
            width = a;
            height = b;
            depth = c;
        }
        else{
            width = 0;
            height = 0;
            depth = 0;
        }
    }
  	float getVolume(){
      return(width*height*depth);
    }
	void scale(float d){
      width = d*width;
      height = d*height;
      depth = d*depth;
    }
    float addVolume(bar3d vol){
        return(getVolume() + vol.getVolume());
    }
};