#include <iostream>
#include <sstream>
#include <cmath>

#include <FL/Fl.H>
#include <FL/gl.h>

#include "gui.hpp"
#include "ogl.hpp"

#include <time.h>
#include <sys/time.h>
#include <math.h>

//timing variables
long long minValue = 0;
long long peakValue = 0;
long long avgValue = 0;
int numberSamples = 0;
int testEnd = 60; //60 seconds
unsigned short captureState = 0;
time_t beginTimer;
timeval elapsed;
  
void Print()
{
    std::cout << "********* RESULT OF TEST ********" << std::endl;
	std::cout << "  Total frames: " << numberSamples << std::endl;
	std::cout << "  Min timer: " << minValue << std::endl;
	std::cout << "  Max timer: " << peakValue << std::endl;
	std::cout << "  Average timer: " << avgValue / numberSamples << std::endl;
	std::cout << "*********************************" << std::endl << std::endl;
}

static void redraw_callback(void * arg) {
  GlGui * window = static_cast<GlGui *>(arg);
  Fl::focus(window);
  window->redraw();
}

GlGui::GlGui(int x, int y, int w, int h, const char * l) : Fl_Gl_Window(x, y, w, h, l) {
  title += l;
  initialized = false;
  Fl::add_idle(redraw_callback, this);
  resizable(this);
}

void GlGui::draw() {
  std::ostringstream oss;

  if(!valid()) {
    if(!initialized) {
      opengl::initialize();
      initialized = true;
    }

    oss << title << " :: OpenGL " << glGetString(GL_VERSION) << " :: " << glGetString(GL_VENDOR);
    label(oss.str().c_str());

    opengl::reshape(w(), h());
  }
  
  opengl::display();
    
  if(captureState == 0)
  {
  	time(&beginTimer);
  	gettimeofday(&elapsed, NULL);
  	captureState = 1;
  }
  else
  {
  	long long prev = (elapsed.tv_sec)*1000000LL + elapsed.tv_usec;
  	gettimeofday(&elapsed, NULL);
  	long long last = (elapsed.tv_sec)*1000000LL + elapsed.tv_usec;
  	
  	long long timerElapse = last - prev;
  	if(captureState == 1)
  	{
  		peakValue = timerElapse;
  		minValue = timerElapse;
  		captureState = 2;
  	}
  	peakValue = std::max(peakValue, timerElapse);
	minValue = std::min(minValue, timerElapse);
	
	avgValue += timerElapse;
	numberSamples++;
	
	time_t t;
	time(&t);
	int currentTime =  difftime(t, beginTimer);
        
	if(currentTime >= testEnd){
		Print();
	  	hide();	
	}
  }
    	
}

int GlGui::handle(int event) {
  if(event == FL_MOUSEWHEEL) {
    opengl::camZ += Fl::event_dy();
    opengl::reshape(w(), h());
    return 1;
  }

  return Fl_Gl_Window::handle(event);
}
