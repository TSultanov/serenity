#include <stddef.h>
#include <X11/Xlib.h>
#include <stdio.h> 
#include <string.h> 

#define WIN_W (260) 
#define WIN_H (160) 

int main()
{
    puts("Starting");
        Display       *d;          /*ディスプレイ構造体へのポインタ*/ 
        Window        w;           /*ウインドウのID*/ 
        XEvent        event;       /*Xイベント構造体*/ 
        GC            gc;          /*グラフィックスコンテキスト*/
        XFontStruct   *xfs;        /*XFontStruct構造体へのポインタ*/
        char          text[256];   /*文字をここに入れる*/ 

        /*helloという文字列を、配列textに入れる*/
        strcpy( text, "hello" );        

        /*ディスプレイをオープン*/
        puts("XOpenDisplay");
        d = XOpenDisplay( NULL ); 

        /* ( 260, 160 ) ピクセルのウインドウを画面左上から( 180, 50 ) 
        のところに作成 */
        puts("XCreateSimpleWindow");
        w = XCreateSimpleWindow( d, RootWindow( d, 0 ), 
                          180, 50, 
                          WIN_W, WIN_H, 
                          1, WhitePixel(d, 0), BlackPixel(d, 0) ); 

        /*GCをXサーバーに作成*/
        puts("XCreateGC");
        gc = XCreateGC( d, w, 0, 0 );

        puts("XLoadQueryFont");
        /*fixedフォントをXサーバーにロード*/
        xfs = XLoadQueryFont ( d, "fixed" );

        puts("XSetFont");
        /*ロードしたフォントをGCに設定*/
        XSetFont ( d, gc, xfs->fid );

        puts("XSelectInput");
        /*再描画のイベントだけを報告するようにする*/
        XSelectInput( d, w, ExposureMask );

        puts("XMapWindow");
        /*作成したウインドウを画面に表示する*/ 
        XMapWindow( d, w ); 

        puts("XFlush");
        /*バッファにたまってるX命令を全部Xサーバーに送る*/ 
        XFlush( d ); 
        
        /* イベントループ */ 
        while( 1 ) {
                puts("XNextEvent");
                XNextEvent( d, &event );

                switch( event.type ) { 
                case Expose:
                        puts("XSetForeground");
                        fflush(stdout);
                        /*描画色を黒にする*/
                        XSetForeground( d, gc, BlackPixel(d, 0) );

                        puts("XFillRectangle");
                        /*画面全体を黒で塗りつぶす*/
                        XFillRectangle( d, w, gc, 0, 0, WIN_W, WIN_H );

                        puts("XSetForeground");
                        /*描画色を白にする*/
                        XSetForeground( d, gc, WhitePixel(d, 0) );

                        puts("XDrawString");
                        /* 配列textに入っている文字をウインドウの左上から20,30のところに書く*/
                        XDrawString( d, w, gc, 20, 30, text, strlen(text) );

                        puts("XFlush");
                        /*XクライアントのバッファにたまってるX命令を全部Xサーバーに送る*/ 
                        XFlush( d ); 

                        /*標準出力に Expose と表示する*/ 
                        printf( "Expose " ); 

                        /*標準出力バッファにたまってる文字を全部標準出力に出す*/ 
                        fflush( stdout ); 
                        break; 
                } 
        } 
}
