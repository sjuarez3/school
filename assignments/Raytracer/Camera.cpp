#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Matrix.h"

using namespace std;

//Author: Steve Juarez
//DOC: November 9, 2014

/* Purpose of program is to ray trace objects in a scene */

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";

//The following code has pieces taken from the ray trace framework given
 
#define N_CHANNELS 3
#define RED 0
#define GREEN 1
#define BLUE 2

#define Ex 5.0
#define Ey 5.0    
#define Ez 5.0

#define Gx 0.0
#define Gy 0.0     
#define Gz 0.0

#define UPx 0.0
#define UPy 0.0    
#define UPz 1.0

#define N 5.0
#define F 25.0

#define THETA 45.0
#define ASPECT 1.0

#define H 512

typedef struct {
    int width, height ;
} window_t ;

typedef struct {
    dmatrix_t UP ;
    dmatrix_t E ;
    dmatrix_t G ;
    dmatrix_t u, v, n ;
    dmatrix_t Mv, Mp ;
    dmatrix_t T1, T2, S1, S2, W ;
    dmatrix_t M ;
} camera_t ;

typedef struct color_t{
    int r, g, b ;
} color_t ;

typedef struct {
    dmatrix_t M ;
    color_t color, specular_color, diffuse_color, ambient_color ;
    double specular_coeff, diffuse_coeff, ambient_coeff ;
    
} object_attributes_t ;

typedef struct {
    dmatrix_t light_position ;
    color_t light_color ;
} light_t ;

dmatrix_t *projection_transform(dmatrix_t *P) {
    
    dmatrix_t *Q ;
    
    Q = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(Q,4,1) ;
    
    if ((P->l == 4) && (P->c == 1)) {
        for (int i = 1 ; i <= 4 ; i++) {
            Q->m[i][1] = P->m[i][1]/P->m[4][1] ;
        }
    }
    return Q ;
}

window_t *build_window(window_t *Window, int height, float aspect) {
    
    Window->height = height ;
    Window->width =  (int) aspect*height ;
    
    return(Window) ;
    
}

camera_t *build_camera(camera_t *Camera, window_t *Window) {
    
    dmat_alloc(&Camera->E,4,1) ;

    Camera->E.m[1][1] = Ex ;
    Camera->E.m[2][1] = Ey ;
    Camera->E.m[3][1] = Ez ;
    Camera->E.m[4][1] = 1.0 ;
    
    dmat_alloc(&Camera->G,4,1) ;
    
    Camera->G.m[1][1] = Gx ;
    Camera->G.m[2][1] = Gy ;
    Camera->G.m[3][1] = Gz ;
    Camera->G.m[4][1] = 1.0 ;

    dmat_alloc(&Camera->n,4,1) ;
    Camera->n = *dmat_normalize(dmat_sub(&Camera->E,&Camera->G)) ;
    Camera->n.l = 3 ;
    
    dmat_alloc(&Camera->UP,4,1) ;
    
    Camera->UP.l = 3 ;
    
    Camera->UP.m[1][1] = UPx ;
    Camera->UP.m[2][1] = UPy ;
    Camera->UP.m[3][1] = UPz ;
    Camera->UP.m[4][1] = 1.0 ;
    
    dmat_alloc(&Camera->u,4,1) ;
    
    Camera->u = *dmat_normalize(dcross_product(&Camera->UP,&Camera->n)) ;
    Camera->v = *dmat_normalize(dcross_product(&Camera->n,&Camera->u)) ;
    
    dmat_alloc(&Camera->Mv,4,4) ;
    
    Camera->Mv.m[1][1] = Camera->u.m[1][1] ;
    Camera->Mv.m[1][2] = Camera->u.m[2][1] ;
    Camera->Mv.m[1][3] = Camera->u.m[3][1] ;
    Camera->Mv.m[1][4] = -1.0*(Camera->E.m[1][1]*Camera->u.m[1][1] +
                               Camera->E.m[2][1]*Camera->u.m[2][1] +
                               Camera->E.m[3][1]*Camera->u.m[3][1]) ;
    
    Camera->Mv.m[2][1] = Camera->v.m[1][1] ;
    Camera->Mv.m[2][2] = Camera->v.m[2][1] ;
    Camera->Mv.m[2][3] = Camera->v.m[3][1] ;
    Camera->Mv.m[2][4] = -1.0*(Camera->E.m[1][1]*Camera->v.m[1][1] +
                               Camera->E.m[2][1]*Camera->v.m[2][1] +
                               Camera->E.m[3][1]*Camera->v.m[3][1]) ;
    
    Camera->Mv.m[3][1] = Camera->n.m[1][1] ;
    Camera->Mv.m[3][2] = Camera->n.m[2][1] ;
    Camera->Mv.m[3][3] = Camera->n.m[3][1] ;
    Camera->Mv.m[3][4] = -1.0*(Camera->E.m[1][1]*Camera->n.m[1][1] +
                               Camera->E.m[2][1]*Camera->n.m[2][1] +
                               Camera->E.m[3][1]*Camera->n.m[3][1]) ;
    
    Camera->Mv.m[4][1] = 0.0 ;
    Camera->Mv.m[4][2] = 0.0 ;
    Camera->Mv.m[4][3] = 0.0 ;
    Camera->Mv.m[4][4] = 1.0 ;
    
    dmat_alloc(&Camera->Mp,4,4) ;
    dmat_identity(&Camera->Mp) ;
    
    float a = -1.0*(F + N)/(F - N) ;
    float b = -2.0*(F*N)/(F - N) ;
    
    Camera->Mp.m[1][1] = N ;
    Camera->Mp.m[2][2] = N ;
    Camera->Mp.m[3][3] = a ;
    Camera->Mp.m[3][4] = b ;
    Camera->Mp.m[4][3] = -1.0 ;
    Camera->Mp.m[4][4] = 0.0 ;
    
    float top = N*tan(M_PI/180.0*THETA/2.0) ;
    float right = ASPECT*top ;
    float bottom = -top ;
    float left = -right ;
    
    dmat_alloc(&Camera->T1,4,4) ;
    
    Camera->T1 = *dmat_identity(&Camera->T1) ;
    
    Camera->T1.m[1][4] = -(right + left)/2.0 ;
    Camera->T1.m[2][4] = -(top + bottom)/2.0 ;
    
    dmat_alloc(&Camera->S1,4,4) ;
    
    Camera->S1 = *dmat_identity(&Camera->S1) ;
    
    Camera->S1.m[1][1] = 2.0/(right - left) ;
    Camera->S1.m[2][2] = 2.0/(top - bottom) ;
    
    dmat_alloc(&Camera->T2,4,4) ;
    dmat_alloc(&Camera->S2,4,4) ;
    dmat_alloc(&Camera->W,4,4) ;
    
    Camera->T2 = *dmat_identity(&Camera->T2) ;
    Camera->S2 = *dmat_identity(&Camera->S2) ;
    Camera->W = *dmat_identity(&Camera->W) ;
    
    Camera->T2.m[1][4] = 1.0 ;
    Camera->T2.m[2][4] = 1.0 ;
    
    Camera->S2.m[1][1] = Window->width/2.0 ;
    Camera->S2.m[2][2] = Window->height/2.0 ;
    
    Camera->W.m[2][2] = -1.0 ;
    Camera->W.m[2][4] = (double)Window->height ;
    
    dmat_alloc(&Camera->M,4,4) ;
    
    Camera->M = *dmat_mult(&Camera->W,dmat_mult(&Camera->S2,dmat_mult(&Camera->T2,dmat_mult(&Camera->S1,dmat_mult(&Camera->T1,dmat_mult(&Camera->Mp,&Camera->Mv)))))) ;
    
    return(Camera) ;
}

/* main method */
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
           "Synthetic Camera",  /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           (int)H*ASPECT,       //width of window
           H,                   //height of window
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);

    HDC hdc = GetDC(hwnd); //Get device handle
    
    double height, width, aspect ; //height, width, and respective aspect ratio of window
    
    camera_t Camera ;
    window_t Window ;
    
    Window = *build_window(&Window,H,ASPECT) ;
    Camera = *build_camera(&Camera,&Window) ;
    dmatrix_t ray, direction ;
       
    aspect = ASPECT ;
    height = N*tan(M_PI/180.0 * THETA/2.0) ;
    width = height*aspect ;
    
    dmat_alloc(&direction,4,1) ;
    dmat_alloc(&ray,4,1) ;
    
    object_attributes_t sphere ;
    
    dmat_alloc(&sphere.M, 4, 4) ;
    
    sphere.M = *dmat_identity(&sphere.M) ;      //generic sphere with radius one centered at origin
    
    sphere.color.r = 0 ;
    sphere.color.g = 1 ;       //sphere color made green
    sphere.color.b = 0 ;
    
    sphere.diffuse_coeff = 0.4 ;
    sphere.ambient_coeff = 0.4 ;
    sphere.specular_coeff = 0.2 ;
    
    sphere.diffuse_color.r = 0 ;
    sphere.diffuse_color.g = 1 ;
    sphere.diffuse_color.b = 0 ;
    
    sphere.ambient_color.r = 0 ;
    sphere.ambient_color.g = 1 ;
    sphere.ambient_color.b = 0 ;
    
    sphere.specular_color.r = 1 ;
    sphere.specular_color.g = 1 ;
    sphere.specular_color.b = 1 ;
    
    light_t light_source ;

    dmat_alloc(&light_source.light_position, 4, 1) ;
    
    light_source.light_color.r = 255 ;
    light_source.light_color.g = 255 ;          //white light source
    light_source.light_color.b = 255 ;
  
    light_source.light_position.m[1][1] = 2 ;
    light_source.light_position.m[2][1] = 3 ;    //light source location set to random place in scene
    light_source.light_position.m[3][1] = 5 ;
    light_source.light_position.m[4][1] = 1 ;       
    
    double a, b, c, t1, t2 ;       //variables used for quadratic equation of sphere intersection points
    
    dmatrix_t s, n, v, r ;     
    
    dmat_alloc(&s, 4, 1) ;    //a vector from the intersection point of the ray and the surface to the light source
    dmat_alloc(&n, 4, 1) ;    //surface normal at ray-surface intersection point
    dmat_alloc(&v, 4, 1) ;    //a vector to the center of projection of the viewing coordinates 
    dmat_alloc(&r, 4, 1) ;    //direction of specular (perfect) reflection
    
    double Id, Is ;           //diffuse and specular intensities
    
    dmatrix_t intersection ;     //point of intersection of ray on sphere surface
    dmat_alloc(&intersection, 4, 1) ;
    
    for (int i = 0 ; i < Window.width ; i++)
    {
        for (int j = 0 ; j < Window.height ; j++) 
        {   
            direction.m[1][1] = -1.0*N*Camera.n.m[1][1] +
                                width*(2.0*i/Window.width - 1.0)*Camera.u.m[1][1] +
                                height*(2.0*j/Window.height - 1.0)*Camera.v.m[1][1] ;
            
            direction.m[2][1] = -1.0*N*Camera.n.m[2][1] +
                                width*(2.0*i/Window.width - 1.0)*Camera.u.m[2][1] +
                                height*(2.0*j/Window.height - 1.0)*Camera.v.m[2][1] ;
            
            direction.m[3][1] = -1.0*N*Camera.n.m[3][1] +
                                width*(2.0*i/Window.width - 1.0)*Camera.u.m[3][1] +
                                height*(2.0*j/Window.height - 1.0)*Camera.v.m[3][1] ;
            
            a = (direction.m[1][1] * direction.m[1][1]) + (direction.m[2][1] * direction.m[2][1]) + (direction.m[3][1] * direction.m[3][1]) ;
            b = (Camera.E.m[1][1] * direction.m[1][1]) + (Camera.E.m[2][1] * direction.m[2][1]) + (Camera.E.m[3][1] * direction.m[3][1]) ;
            c = (Camera.E.m[1][1] * Camera.E.m[1][1]) + (Camera.E.m[2][1] * Camera.E.m[2][1]) + (Camera.E.m[3][1] * Camera.E.m[3][1]) - 1 ;   
            
            /* ray intersects sphere */
            if(((b*b) - (a*c)) >= 0 )        
            {
                   /*calculate exact point of intersection at t */
                   t1 = (-1.0*(b/a)) + (sqrt(((b*b) - (a*c))) / a) ;
                   t2 = (-1.0*(b/a)) - (sqrt(((b*b) - (a*c))) / a) ;
                
                   direction.m[1][1] *= min(t1,t2) ;
                   direction.m[2][1] *= min(t1,t2) ;
                   direction.m[3][1] *= min(t1,t2) ;
                   
                   intersection = *dmat_add(&Camera.E, &direction) ; //r(t) = e + dt
                   
                   s.m[1][1] = light_source.light_position.m[1][1] - intersection.m[1][1] ;
                   s.m[2][1] = light_source.light_position.m[2][1] - intersection.m[2][1] ;
                   s.m[3][1] = light_source.light_position.m[3][1] - intersection.m[3][1] ;
                
                   n.m[1][1] = intersection.m[1][1] ;
                   n.m[2][1] = intersection.m[2][1] ;
                   n.m[3][1] = intersection.m[3][1] ;
                
                   /* calculate diffuse intensity */
                   Id = sphere.diffuse_coeff*((s.m[1][1] * n.m[1][1]) + (s.m[2][1] * n.m[2][1]) + (s.m[3][1] * n.m[3][1])) ;
                   if(Id < 0) Id = 0.0 ;
                   
                   v.m[1][1] = Camera.E.m[1][1] - intersection.m[1][1] ;
                   v.m[2][1] = Camera.E.m[2][1] - intersection.m[2][1] ;
                   v.m[3][1] = Camera.E.m[3][1] - intersection.m[3][1] ;
                   
                   r.m[1][1] = -1*s.m[1][1] + (2*(((s.m[1][1] * n.m[1][1]) + (s.m[2][1] * n.m[2][1]) + (s.m[3][1] * n.m[3][1])) /
                               ((n.m[1][1] * n.m[1][1]) + (n.m[2][1] * n.m[2][1]) + (n.m[3][1] * n.m[3][1])))*n.m[1][1]) ;
                               
                   r.m[2][1] = -1*s.m[2][1] + (2*(((s.m[1][1] * n.m[1][1]) + (s.m[2][1] * n.m[2][1]) + (s.m[3][1] * n.m[3][1])) / 
                               ((n.m[1][1] * n.m[1][1]) + (n.m[2][1] * n.m[2][1]) + (n.m[3][1] * n.m[3][1])))*n.m[2][1]) ; 
                                         
                   r.m[3][1] = -1*s.m[3][1] + (2*(((s.m[1][1] * n.m[1][1]) + (s.m[2][1] * n.m[2][1]) + (s.m[3][1] * n.m[3][1])) / 
                               ((n.m[1][1] * n.m[1][1]) + (n.m[2][1] * n.m[2][1]) + (n.m[3][1] * n.m[3][1])))*n.m[3][1]) ;
                   
                   /* calculate specular intensity */
                   Is = sphere.specular_coeff*(pow(((v.m[1][1] * r.m[1][1]) + (v.m[2][1] * r.m[2][1]) + (v.m[3][1] * r.m[3][1])), 10)) ;
                   if(Is < 0) Is = 0.0 ;
                
                   /* transform point of intersection to point on screen */
                   intersection = *dmat_mult(&Camera.M, &intersection) ;
                   intersection = *projection_transform(&intersection) ;
                   
                   /* calculate pixel with calculated light intensity */
                   SetPixel(hdc, i, j,
                   RGB(light_source.light_color.r*sphere.color.r*Id*sphere.diffuse_color.r*sphere.ambient_coeff*sphere.ambient_color.r*sphere.specular_color.r,
                       light_source.light_color.g*sphere.color.g*Id*sphere.diffuse_color.g*sphere.ambient_coeff*sphere.ambient_color.g*sphere.specular_color.g,
                       light_source.light_color.b*sphere.color.b*Id*sphere.diffuse_color.b*sphere.ambient_coeff*sphere.ambient_color.b*sphere.specular_color.b)) ;
            }
            /* ray misses sphere, set pixel to black */
            else              
                   SetPixel(hdc, i, j, RGB(0,0,0)) ;
        }
    }
    
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
