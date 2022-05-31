float x,y;

void setup(){
  size(400,400);
  x=0;
  y=200;
}

void draw(){
  background(255);
  x++;
  y=20*sin(radians(x*3))+200;
  quad(x,y,x+100,y,x+75,y+25,x+25,y+25);
}
