
void servosWrite() {
  
  // write positions
  for (int i = 0; i < 6; i++)
  {
    write(i);
  }
}

void write(int s) {
  servo[s].writeMicroseconds(servoMin + int(pos[s]));
}
