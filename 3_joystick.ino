
void readValues() {
  for (int i = 0; i < 6; i++)
  {

    // read pot value, convert to signed value
    float value = (analogRead(pots[i]) - centers[i]);

    // check if value is below threshold
    if (value < deadzone && value > -deadzone)
    {
      // Zero value
      value = 0;
    }

    // Rescale and raise to third power to get curve and add weight
    value = (pow(0.1 * value, 3) / 125000) * weights[i];

    // Do smoothing on increment value
    if (value == 0)
    {
      // use tf for stopping
      incrs[i] = tf_stop * value + (1 - tf_stop) * incrs[i];
    } else {
      // use tf for motion smoothin
      incrs[i] = tf * value + (1 - tf) * incrs[i];
    }


    // Update position value
    pos[i] = pos[i] + incrs[i];

    // limit value
    if (pos[i] > servoRange) {
      pos [i] = servoRange;
    }
    if (pos[i] < 0) {
      pos [i] = 0;
    }
  }
}
