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
};
