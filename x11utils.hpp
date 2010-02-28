#include <X11/Xlib.h>
#include <X11/keysym.h>

XKeyEvent createKeyEvent(Display *display, Window &win,
                           Window &winRoot, bool press,
                           int keycode, int modifiers)
{
   XKeyEvent event;

   event.display     = display;
   event.window      = win;
   event.root        = winRoot;
   event.subwindow   = None;
   event.time        = CurrentTime;
   event.x           = 1;
   event.y           = 1;
   event.x_root      = 1;
   event.y_root      = 1;
   event.same_screen = True;
   event.keycode     = XKeysymToKeycode(display, keycode);
   event.state       = modifiers;

   if(press)
     event.type = KeyPress;
   else
     event.type = KeyRelease;

   return event;
}

int presskey(int keycode){

   Display *display = XOpenDisplay(0);
   if(display == NULL)
      return -1;
   Window winRoot = XDefaultRootWindow(display);
   Window winFocus;
   int    revert;
   XGetInputFocus(display, &winFocus, &revert);
   XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, keycode, 0);
   XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
   event = createKeyEvent(display, winFocus, winRoot, false, keycode, 0);
   XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
   


   //XWarpPointer(display, None, None, 0,0,0,0, keycode1,keycode2);

   XCloseDisplay(display);
}
   
   
void mouseClick(int button)
{
	Display *display = XOpenDisplay(NULL);

	XEvent event;
	
	if(display == NULL)
	{
		fprintf(stderr, "Errore nell'apertura del Display\n");
		exit(EXIT_FAILURE);
	}
	
	memset(&event, 0x00, sizeof(event));
	
	event.type = ButtonPress;
	event.xbutton.button = button;
	event.xbutton.same_screen = True;
	
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	
	event.xbutton.subwindow = event.xbutton.window;
	
	while(event.xbutton.subwindow)
	{
		event.xbutton.window = event.xbutton.subwindow;
		
		XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	}
	
	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");
	
	XFlush(display);
	
	usleep(100000);
	
	event.type = ButtonRelease;
	event.xbutton.state = 0x100;
	
	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");
	
	XFlush(display);
	
	XCloseDisplay(display);
}
