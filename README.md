# IOT-Based-Quadcopter
This is a Quadcopter controlled through internet via a android application. Please refer and understand how we can make communication between Nodemcu and a firebase, learn to create a realtime database in firebase and also understand how to connect mitapp to nodemcu via firbase. This is a prototype for a DIY Quadcopter with unlimited range. Please make use of it for further inovation and hobbies. 

I extend my sincere gratitude to Joop Broking youtube channel for a comperhencive playlist (https://www.youtube.com/watch?v=2pHdO8m6T7c&list=PLPthmMr7vKySs8WjFCb_QnYbfEXOOrocy) regarding building a quadcopter. 

Please watch that for reference, but not everything is the same becasuse the video is about radio controlled drone, but ours is controlled via internet.


#STEP 1
Make the connetion as per the schematic provided.

The component used are
1. electronic speed controller * 4
2. 920kv brushless motor * 4
3. MPU6050 
4. Arduino uno
5. 8 inch propeller * 4
6. Nodemcu
7. 11.1v Lipo 3 cell battery
8. S500 Frame
9. 9v battery

#STEP 2
After making the connection Load the Setup file to Arduino and run, keep the drone stable while running the code.

#STEP 3
After that load ESC_Calibration code to Arduino and Run the code. Follow the instruction as promted in serial monitor

#STEP 4
After that load the Flight_controler code. 

#STEP 5
After that load the Radio_sim code to the Nodemcu and run it. Make sure that it can successfully connect to the googe firebase realtime database.

#STEP 6
Open the MITApp inventor app and load the code given. This is the application through which we will controll the drone.

#STEP 7
Callibration is very important, in step 3 the overall vibration value must stay bellow 55. You can use insulation tape on top of proppeller leaf to reduce friction thus reducing vibration.

#STEP 8 
Fire up the Quadcopter wait for the beep, then connect the power to arduino and Nodemcu. Then your good to go. If we keep a wifi dongle on top of the drone we have more wider network coverage.



