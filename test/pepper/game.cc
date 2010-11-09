#include <crml-core>
#include <crml-gfx>

using namespace crml;

int main() {
  Display dsp;
  dsp.Check();
  Image img1("gopher.png"); 
  Coord c1(0, 0);
  Sprite spr1(img1, c1);

  while(Core::Running()){
    dsp.ShowAt(c1, spr1);    
    c1.MoveX(1);
  } 
}
