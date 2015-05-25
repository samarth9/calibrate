# calibrate
Use for getting the range of HSV values of the target object

1. save the video of the target object
2. change the path of the video at line 35
3. if working on live video then uncomment line34 and comment line35
4. use the following commands :-
  a. cmake .
  b. make
  c. ./calibrate
5. pause at the moment when the object is visible clearly using space/esc key
6. use the trackbars to change the hsv range untill the image is thresholded(foreground(object) should be white)
7. exit using esc key and ranges will pe printed
