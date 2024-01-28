#include "helpers.h"
#include <math.h> //round
#include <stdlib.h> //malloc

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int rows = 0 ; rows < height ; rows ++){
        for(int col = 0; col < width ; col ++){
            float greyf = ((image[rows][col].rgbtBlue + image[rows][col].rgbtGreen + image[rows][col].rgbtRed) / 3.0);
            int grey = round(greyf);

            image[rows][col].rgbtBlue = grey ;
            image[rows][col].rgbtGreen = grey;
            image[rows][col].rgbtRed = grey;

        }
    }
    return;
}
            //   if((greyf - grey) >.5){
            //     grey++;
            //   }
            //   image[rows][col] = grey ;

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int rows = 0 ; rows < height ; rows ++){
        for(int col = 0; col < width ; col ++){
            int red = round(.393 * image[rows][col].rgbtRed + .769 * image[rows][col].rgbtGreen + .189 * image[rows][col].rgbtBlue);
            int green =  round(.349 * image[rows][col].rgbtRed + .686 * image[rows][col].rgbtGreen + .168 * image[rows][col].rgbtBlue);
            int blue =  round(.272 * image[rows][col].rgbtRed + .534 * image[rows][col].rgbtGreen + .131 * image[rows][col].rgbtBlue);

            if (red > 255){
                red = 255;
            }
            if (green > 255){
                green = 255;
            }
            if (blue > 255){
                blue = 255;
            }

            image[rows][col].rgbtRed = red;
            image[rows][col].rgbtGreen = green;
            image[rows][col].rgbtBlue = blue;

            }

        }
    return;
    }


 // if(col == 2 && rows == 2){
            // printf("red :%f ,green:%f,blue:%f \n",red,green,blue);
            // printf("red :%i ,green:%i,blue:%i \n",*(image[rows][col]),*(image[rows][col].rgbtGreen),*(image[rows][col].rgbtBlue));

            // if (image[rows][col].rgbtRed > 255){
            //     image[rows][col].rgbtRed = 255;
            // }
            // if (image[rows][col].rgbtGreen > 255){
            //     image[rows][col].rgbtGreen = 255;
            // }
            // if (image[rows][col].rgbtBlue > 255){
            //     image[rows][col].rgbtBlue = 255;
            // }

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
   for(int col = 0; col < (width/2) ; col ++){
        for(int rows = 0 ; rows < height ; rows ++){
        // image[rows][width-col];
        //svae to swap
            int blue = image[rows][col].rgbtBlue;
            int green = image[rows][col].rgbtGreen;
            int red = image[rows][col].rgbtRed;
            //swap a
            image[rows][col].rgbtBlue = image[rows][width-col-1].rgbtBlue ;
            image[rows][col].rgbtGreen = image[rows][width-col-1].rgbtGreen;
            image[rows][col].rgbtRed = image[rows][width-col-1].rgbtRed;
            //swap b
            image[rows][width-col-1].rgbtBlue = blue ;
            image[rows][width-col-1].rgbtGreen = green;
            image[rows][width-col-1].rgbtRed = red;
        }
    }
    return;
}


void blur(int height, int width, RGBTRIPLE image[height][width]) {

    RGBTRIPLE t[height][width];

    for(int row = 0; row < height ; row ++){
   		for(int col = 0 ; col < width ; col ++) {
            int sumred = 0;
            int sumgreen = 0;
            int sumblue = 0;
            int count = 0;
            for(int row_1 = row - 1; row_1 <= row + 1 ; row_1 ++) {
                for(int col_1 = col - 1 ; col_1 <= col + 1 ; col_1 ++) {
                    if (row_1 < 0 || row_1 >= height || col_1 < 0 || col_1 >= width)
                        continue;
                    sumred += image[row_1][col_1].rgbtRed;
                    sumgreen += image[row_1][col_1].rgbtGreen;
                    sumblue += image[row_1][col_1].rgbtBlue;
                    count += 1;
        	    }
            }
                t[row][col].rgbtBlue = round(sumblue * 1.0 / count );
                t[row][col].rgbtGreen = round(sumgreen * 1.0 / count ) ;
                t[row][col].rgbtRed = round(sumred * 1.0 / count );
    	    }
		}
        for(int col = 0; col < width ; col ++){
            for(int row = 0 ; row < height ; row ++)
                {
                    image[row][col].rgbtRed = t[row][col].rgbtRed;
                    image[row][col].rgbtGreen = t[row][col].rgbtGreen;
                    image[row][col].rgbtBlue =  t[row][col].rgbtBlue;
                }
        }
}


// Blur image
// void blur(int height, int width, RGBTRIPLE image[height][width])
// {
//      RGBTRIPLE t[height][width];

//           //hna hbdti a5od l blured value fil t
//           //take old pixels value
//      for(int col = 0; col < width ; col ++){
//        for(int rows = 0 ; rows < height ; rows ++)
//         {
//           int sumred = 0;
//           int sumgreen = 0;
//           int sumblue = 0;

//           int around = 0;

//           int aroundcol = col-1 ;
//           int aroundrow = rows-1 ;
//           while(aroundcol <0){
//             aroundcol ++;
//           }
//           while(aroundrow < 0){
//             aroundrow ++;
//           }
//           while(-1<aroundcol && aroundcol <width && aroundcol < (col + 2)){
//             while(-1<aroundrow && aroundrow <height && aroundrow < (rows + 2)){
//                 sumred = sumred + image[aroundrow][aroundcol].rgbtRed;
//                 sumgreen = sumgreen + image[aroundrow][aroundcol].rgbtGreen;
//                 sumblue = sumblue + image[aroundrow][aroundcol].rgbtBlue;
//                 around ++;
//                 aroundrow ++;
//             }
//             aroundcol ++;
//           }
//           int newred = round(sumred/around) ;
//           int newgreen = round(sumgreen / around) ;
//           int newblue = round(sumblue / around) ;
//           if(newred>255){
//             newred=255;
//           }
//           if(newgreen>255){
//             newgreen=255;
//           }
//           if(newblue>255){
//             newblue=255;
//           }

//           t[rows][col].rgbtBlue = newblue;
//           t[rows][col].rgbtGreen = newgreen ;
//           t[rows][col].rgbtRed = newred ;
//         }
//      }

//      for(int col = 0; col < width ; col ++){
//        for(int rows = 0 ; rows < height ; rows ++)
//         {   image[rows][col].rgbtRed = t[rows][col].rgbtRed;
//             image[rows][col].rgbtGreen = t[rows][col].rgbtGreen;
//             image[rows][col].rgbtBlue =  t[rows][col].rgbtBlue;

//         }
//      }
//      return;
// }



// *(image[rows][col].rgbtRed) = *(t[rows][col].rgbtRed);
//             *(image[rows][col].rgbtGreen) = *(t[rows][col].rgbtGreen);
//             *(image[rows][col].rgbtBlue) =  *(t[rows][col].rgbtBlue);


//         //   int newred = round(sumred/around) ;
//         //   int newgreen = round(sumgreen / around) ;
//         //   int newblue = round(sumblue / around) ;


//     //  RGBTRIPLE* t = malloc(height*width);;
//     //  if (t ==NULL){
//     //    return 1;
//     //  }

// char* s = "hi";
// // char* t = s ; ksa t = 0x pointer l mkan l "h" w ay t3dil 3l t yb2a fil s brdo
// //lw 3yza copy b fdi mkan fil ram a7ot fih ali fil s

// //bfdi mkan fil ram l 3dd 7rof fil s +1 ll \0
// char* t = malloc(strlen(s)+1);

// //lazm 34an mmkn l memory ton mlyana a7ot condition
// if (t==NULL){
//     return 1;
// }

// //hmla kol t[]bl mo2ablha fil s[]
//     for(int i=0; i<=strlen(s)+1;i++ ){
//        t[i]=s[i]
// }

// // mmkn bdl ma 3ml l loop 7ot l data ali fil s fil t b strcop(,)
// srtcpy(t,s);




// t[0]= toupper(t[0]);
// printf("s:%s\n",s);
// printf("t:%s\n",t);

// // lazm andf b3d ma a5ls w atcheck bl $ help50 valgrind ./5-malloc
// free(t);



