/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//#include "filler.h"

animation filler::fillSolidDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                 double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
    solidColorPicker solidCP(fillColor);
    return fill<Stack>(img, x, y, solidCP, tolerance, frameFreq);
}

animation filler::fillGridDFS(PNG& img, int x, int y, HSLAPixel gridColor,
                                int gridSpacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
    gridColorPicker gridCP(gridColor,gridSpacing);
    return fill<Stack>(img, x, y, gridCP, tolerance, frameFreq);
}

animation filler::fillGradientDFS(PNG& img, int x, int y,
                                    HSLAPixel fadeColor1, HSLAPixel fadeColor2,
                                    int radius, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
    gradientColorPicker gradCP(fadeColor1,fadeColor2,radius,x,y);
    return fill<Stack>(img, x, y, gradCP, tolerance, frameFreq);
}

// animation filler::fillRainDFS(PNG& img, int x, int y,
//                                     long double freq, double tolerance, int frameFreq)
// {
//     /**
//      * @todo Your code here! You should replace the following line with a
//      * correct call to fill with the correct colorPicker parameter.
//      */
//     // rainbowColorPicker a(freq);
//     return fill<Stack>(img, x, y, a, tolerance, frameFreq);
// }

animation filler::fillSolidBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                 double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
    solidColorPicker solidCP(fillColor);
    return fill<Queue>(img, x, y, solidCP, tolerance, frameFreq);
}

animation filler::fillGridBFS(PNG& img, int x, int y, HSLAPixel gridColor,
                                int gridSpacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
    gridColorPicker gridCP(gridColor,gridSpacing);
    return fill<Queue>(img, x, y, gridCP, tolerance, frameFreq);
}

animation filler::fillGradientBFS(PNG& img, int x, int y,
                                    HSLAPixel fadeColor1, HSLAPixel fadeColor2,
                                    int radius, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
    gradientColorPicker gradCP(fadeColor1,fadeColor2,radius,x,y);
    return fill<Queue>(img, x, y, gradCP, tolerance, frameFreq);
}
// animation filler::fillRainBFS(PNG& img, int x, int y,
//                                     long double freq, double tolerance, int frameFreq)
// {
//     /**
//      * @todo Your code here! You should replace the following line with a
//      * correct call to fill with the correct colorPicker parameter.
//      */
//     // rainbowColorPicker a(freq);
//     return fill<Queue>(img, x, y, a, tolerance, frameFreq);
// }

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    /**
     * @param img Image to do the filling on.
     * @param x X coordinate to start the fill from.
     * @param y Y coordinate to start the fill from.
     * @param fillColor The colorPicker to be used for the fill.
     * @param tolerance How far away colors are allowed to be to still be
     *  included in the fill.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. For instance, if frameFreq == 1, a frame is added when every
     *  pixel is filled. If frameFreq == 10, a frame is added after every 10
     *  pixels is filled.
     * @return An animation that shows the fill progressing over the image.
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure. 
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are 
     *              within (or equal to) tolerance distance from the center, 
     *              to the ordering structure, and
     *              mark them as processed.
     *        2.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        **RIGHT(+x),0014474 DOWN(+y), LEFT(-x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's RIGHT, then the one DOWN from it, then to the LEFT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */
     //
     // OrderingStructure<??> order;
     // Place given point in the ordering structure
     
     animation a;
     

     OrderingStructure<HSLAPixel*> points;
     OrderingStructure<int> xC;
     OrderingStructure<int> yC; 
     int frameCount = 0;     

     //keep track of processed
     vector<vector<bool>> processed;
     for(unsigned int i = 0; i < img.height(); i++){
         vector<bool> horizontal;
         for(unsigned int j = 0; j < img.width(); j++){
             horizontal.push_back(false);
         }
         processed.push_back(horizontal);
     }

     // color to color on the new pixel;
     // change color
     HSLAPixel newColor = fillColor(x,y);
     HSLAPixel * curPix = img.getPixel(x,y);
     //original pixel to compare to
     HSLAPixel  strPix =* curPix;
     *curPix = newColor;
     //color it by assigning some value in curPix 
     //pass it into ordering structure
     xC.add(x);
     yC.add(y);
     points.add(curPix);
     processed[y][x] = true;

      if(frameCount%frameFreq == 0){
             a.addFrame(img);
      }
 
     while(!points.isEmpty()){
         //take out current point 
         HSLAPixel* cur = points.remove();
         unsigned int xCur = xC.remove();
         unsigned int yCur = yC.remove();

         //check if RIGHT(+X) neighbour within tolerance
         HSLAPixel* right = img.getPixel(xCur+1,yCur);
         if(right->dist(strPix)<=tolerance && xCur+1 < img.width() && yCur < img.height() && !processed[yCur][xCur+1 ]){
             //change processed
             processed[yCur][xCur+1] = true;

             //color point
             HSLAPixel nC = fillColor(xCur+1, yCur);
             *right = nC;

             points.add(right);
             xC.add(xCur+1);
             yC.add(yCur);

             frameCount++;
              if(frameCount%frameFreq == 0){
             a.addFrame(img);
              }
         }

        //check if DOWN(+y) neighbour within tolerance
         HSLAPixel* down = img.getPixel(xCur,yCur+1);
         if(down->dist(strPix)<=tolerance && xCur < img.width() && yCur+1 < img.height() && !processed[yCur+1][xCur]){
             processed[yCur+1][xCur] = true;
             HSLAPixel nC = fillColor(xCur,yCur+1);
             *down = nC;

             points.add(down);
             xC.add(xCur);
             yC.add(yCur+1);
             frameCount++;
              if(frameCount%frameFreq == 0){
             a.addFrame(img);
              }
         }

         //check if LEFT(-X) neighbour within tolerance
         HSLAPixel* left = img.getPixel(xCur-1,yCur);
         if(left->dist(strPix)<=tolerance && xCur-1 < img.width() && yCur < img.height() && !processed[yCur][xCur-1 ]){
             processed[yCur][xCur-1] = true;
             HSLAPixel nC = fillColor(xCur-1, yCur);
             *left = nC;

             points.add(left);
             xC.add(xCur-1);
             yC.add(yCur);

             frameCount++;
              if(frameCount%frameFreq == 0){
             a.addFrame(img);
              }
         }

         //check if UP(-y) neighbour within tolerance
         HSLAPixel* up = img.getPixel(xCur,yCur-1);
         if(up->dist(strPix)<=tolerance && xCur < img.width() && yCur-1 < img.height() && !processed[yCur-1][xCur]){
             processed[yCur-1][xCur] = true;
             HSLAPixel nC = fillColor(xCur,yCur-1);
             *up = nC;

             points.add(up);
             xC.add(xCur);
             yC.add(yCur-1);
             frameCount++;
             if(frameCount%frameFreq == 0){
             a.addFrame(img);
             }
        }   
     }
    
    a.addFrame(img);
    return a;
} 
