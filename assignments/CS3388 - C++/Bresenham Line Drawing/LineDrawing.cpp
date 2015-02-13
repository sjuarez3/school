#include <windows.h>

//Author: Steve Juarez
//DOC: September 18, 2014
/* The purpose of this program is to open a window and
draw lines using Bresenham's Line Drawing Algorithm */

//Comments using these /**/ are auto-generated comments
//from the Dev-C++ auto-generated Win32-based application

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";

//drawLine
//Author: Steve Juarez
//DOC: September 18, 2014
//Draws a line in a window from (x1, y1) to (x2, y2) using Bresenham's Line Algorithm
//int @x1 starting point x coordinate
//int @y1 starting point y coordinate
//int @x2 end point x coordinate
//int @y2 end point y coordinate
//int @red RGB red value for the line
//int @green RGB green value for the line
//int @blue RGB blue value for the line
//HDC @hdc device handle

void drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue, HDC hdc)
{
     int p;
     int dy = y2-y1;      
     int dx = x2-x1;      
     
     if(dx == 0)
           return;    
           
     double m = dy/dx;    //slope of the line
     
     if(m > 1 && dy > 0 && dx > 0)
     {
          /////////////Case: 1 < m < infinity//////////////////////
          SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots start point
          for(int i = y1; i < y2; i++)
          {
            if(i == y1)
            {
                    p = (2*(dx))-(dy);
            }
            else
            {
                if(p < 0)
                {
                        p = p+(2*(dx));
                }
                else
                {
                    p = p+(2*(dx))-(2*(dy));
                    x1++; 
                }
            y1++;
            SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots next pixel
            }
          }
     }
     else if(m < -1 && dx < 0 && dy > 0)
     {
          /////////////Case: -infinity < m < -1//////////////////////
          SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots start point
          for(int i = y1; i < y2; i++)
          {
            if(i == y1)
            {
                    p = (2*(-dx))-(dy);
            }
            else
            {
                if(p < 0)
                {
                        p = p+(2*(-dx));
                }
                else
                {
                    p = p+(2*(-dx))-(2*(dy));
                    x1--; 
                }
                y1++;
                SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots next pixel
            }
          }
     }
     else if(-1 <= m && m <= 0 && dx < 0 && dy > 0)
     {
          /////////////Case: -1 <= m <= 0//////////////////////
          SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots start point
          for(int i = x1; i > x2; i--)
          {
            if(i == x1)
            {
                    p = (2*(dy))-(-dx);
            }
            else
            {
                if(p < 0)
                {
                        p = p+(2*(dy));
                }
                else
                {
                    p = p+(2*(dy))-(2*(-dx));
                    y1++; 
                }
                x1--;
                SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots next pixel
            }
          }
     }
     else if(m <= 0 && m >= -1 && dy < 0 && dx > 0)
     {
          /////////////Case: -1 <= m < 0//////////////////////
          SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots start point
          for(int i = x1; i < x2; i++)
          {
            if(i == x1)
            {
                    p = (2*(-dy))-(dx);
            }
            else
            {
                if(p < 0)
                {
                        p = p+(2*(-dy));
                }
                else
                {
                    p = p+(2*(-dy))-(2*(dx));
                    y1--; 
                }
                x1++;
                SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots next pixel
            }
          }
     }
     else if(m < -1 && dy < 0 && dx > 0)
     {
          /////////////Case: -infinity < m < -1//////////////////////
          SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots start point
          for(int i = y1; i > y2; i--)
          {
            if(i == y1)
            {
                    p = (2*(dx))-(-dy);
            }
            else
            {
                if(p < 0)
                {
                        p = p+(2*(dx));
                }
                else
                {
                    p = p+(2*(dx))-(2*(-dy));
                    x1++; 
                }
                y1--;
                SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots next pixel
            }
          }    
     }
     else if(m > 1 && dy < 0 && dx < 0)
     {
           /////////////Case: 1 < m < infinity//////////////////////
           SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots start point
           for(int i = y1; i > y2; i--)
           {
            if(i == y1)
            {
                    p = (2*(-dx))-(-dy);
            }
            else
            {
                if(p < 0)
                {
                        p = p+(2*(-dx));
                }
                else
                {
                    p = p+(2*(-dx))-(2*(-dy));
                    x1--; 
                }
                 y1--;
                 SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots next pixel
            }
           }
     }
     else if(m >= 0 && m <= 1 && dy < 0 && dx < 0)
     {
          /////////////Case: 0 <= m <= 1//////////////////////
          SetPixel(hdc, x1,y1, RGB(red, green, blue)); //plots start point
          for(int i = x1; i > x2; i--)
          {
            if(i == x1)
            {
                    p = (2*(-dy))-(-dx);
            }
            else
            {
                if(p < 0)
                {
                        p = p+(2*(-dy));
                }
                else
                {
                    p = p+(2*(-dy))-(2*(-dx));
                    y1--; 
                }
                x1--;
                SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots next pixel
            }
          }
     }
     else
     {
         /////////////Case: 0 <= m <= 1//////////////////////
         SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots start point
         for(int i = x1; i < x2; i++)
         {
            if(i == x1)
            {
                    p = (2*(dy))-(dx);
            }
            else
            {
                if(p < 0)
                {
                        p = p+(2*(dy));
                }
                else
                {
                    p = p+(2*(dy))-(2*(dx));
                    y1++; 
                }
                x1++;
                SetPixel(hdc, x1, y1, RGB(red, green, blue)); //plots next pixel
            }
         }
     }
}

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    
    //Use white as the background of the window
    wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Line Drawing",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           512,                 //change window width to 512
           512,                 //change window height to 512
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);

    HDC hdc = GetDC(hwnd); //Get device handle
    
    drawLine(256, 256, 456, 356, 0, 250, 0, hdc);     //green line
    drawLine(256, 256, 356, 456, 250, 0, 0, hdc);     //red line
    drawLine(256, 256, 156, 456, 0, 0, 250, hdc);     //blue line
    drawLine(256, 256, 56, 356, 250, 250, 0, hdc);    //yellow line
    drawLine(256, 256, 456, 156, 250, 0, 250, hdc);   //purple line
    drawLine(256, 256, 356, 56, 0, 250, 250, hdc);    //turquoise line
    drawLine(256, 256, 156, 56, 255, 105, 0, hdc);    //orange line
    drawLine(256, 256, 56, 156, 139, 119, 109, hdc);  //brown line
    
    
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        // quits program when user presses 'q'
        case WM_KEYDOWN:
             VK_MENU;         //Alt key in combination with
             if(wParam == 'Q')      //'Q' in virtual key code produces 'q'
             {
                       DestroyWindow(hwnd); //destroys window
                       return 0;
             }
             break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
