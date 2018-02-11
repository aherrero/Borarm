void Home() { //Call this fucntion when u want to set arm in home position

  shoulder.write(77);
  delay(200);
  elbow.write(95);
  delay(200);
  base.write(80);
  delay(200);

}

void Pick() { // This is fixed pick place.  
  
  pinch.write(130);
  base.write(155);
  delay(200);
  shoulder.write(128);
  delay(200);
  elbow.write(94);
  delay(300);
  pinch.write(105);
  delay(100);

}

