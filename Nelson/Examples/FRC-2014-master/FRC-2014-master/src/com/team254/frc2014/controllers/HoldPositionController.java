package com.team254.frc2014.controllers;

import com.team254.frc2014.Constants;
import com.team254.lib.Controller;
import com.team254.lib.util.ChezyMath;

/**
 * HoldHeadingController.java
 * This holds the robot in place.
 * @author Tom Bottiglieri
 */
public class HoldPositionController extends Controller {

  private double kpTurn = Constants.headingKp.getDouble();
  private double kiTurn = Constants.headingKi.getDouble();
  private double kDrive = .9;
  protected double heading = 0;
  private double distance = 0;
  
  public void setHeading(double h) {
    heading = h;
  }
  public void setDistance(double d) {
    distance = d;
  }
  double sumError = 0;
  public void update() {
    if (!enabled) {
      return;
    }
    kpTurn = Constants.headingKp.getDouble();
    kiTurn = Constants.headingKi.getDouble();
    double angleDiff = ChezyMath.boundAngleNeg180to180Degrees(heading - drivebase.getGyroAngle());
    if (Math.abs(angleDiff) < 15) {
      sumError += angleDiff;
    } 
    else {
      sumError = 0;
    }
    
    if (Math.abs(angleDiff) > 20) {
      kpTurn = Constants.headingKpFar.getDouble();          
    }
  
    double turn = (kpTurn * angleDiff);
    double speed = (distance - drivebase.getAverageDistance()) * kDrive;
    drivebase.setLeftRightPower(speed + turn, speed - turn);
  }

  public void reset() {
    sumError = 0;
  }
  
  public double getGoal() {
    return 0;
  }
}

