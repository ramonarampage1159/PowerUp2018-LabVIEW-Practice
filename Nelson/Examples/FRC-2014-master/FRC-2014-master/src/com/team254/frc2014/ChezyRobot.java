package com.team254.frc2014;

import com.team254.frc2014.controllers.HoldPositionController;
import com.team254.lib.OpenLoopController;
import com.team254.frc2014.controllers.RpmFlywheelController;
import com.team254.frc2014.controllers.SteerableHoldPositionController;
import com.team254.frc2014.controllers.TrajectoryDriveController;
import com.team254.frc2014.hotgoal.BannerHotGoalDetector;
import com.team254.frc2014.hotgoal.CheesyVisionHotGoalDetector;
import com.team254.frc2014.subsystems.*;
import com.team254.lib.MultiLooper;
import edu.wpi.first.wpilibj.AnalogChannel;
import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Solenoid;
import edu.wpi.first.wpilibj.Talon;

/**
 * ChezyRobot defines all of the subsystems.
 *
 * @author Tom Bottiglieri (tom@team254.com)
 */
public class ChezyRobot {

  static {
    poke();
  }

  // this method does nothing. It is here to combat Java's lazy loading of static classes.
  private static void poke() {} 
  
  // Subsystems
  public static final Drivebase drivebase = new Drivebase();
  public static final Shooter shooter = new Shooter();
  public static final Compressor compressor = new Compressor(Constants.pressureSwitch.getInt(), Constants.compressorRelay.getInt());
  public static final Pinniped pinniped = new Pinniped();
  
  // Set up the intakes
  public static final Talon frontIntakeRoller = new Talon(Constants.frontIntakeRollerPort.getInt());
  public static final Solenoid frontIntakeSolenoid = new Solenoid(Constants.frontIntakeSolenoidPort.getInt());
  public static final AnalogChannel frontIntakeSwitch = new AnalogChannel(Constants.frontIntakeSwitchPort.getInt());
  
  public static final Talon rearIntakeRoller = new Talon(Constants.rearIntakeRollerPort.getInt());
  public static final Solenoid rearIntakeSolenoid = new Solenoid(Constants.rearIntakeSolenoidPort.getInt());
  public static final AnalogChannel rearIntakeSwitch = new AnalogChannel(Constants.rearIntakeSwitchPort.getInt());
  
  public static final Intake frontIntake = new Intake("Front Intake", frontIntakeRoller, frontIntakeSwitch, frontIntakeSolenoid, true, 1.0);
  public static final Intake rearIntake = new Intake("Rear Intake", rearIntakeRoller, rearIntakeSwitch, rearIntakeSolenoid, true, .65);
  
  public static final CheesyDriveHelper cdh = new CheesyDriveHelper(drivebase);
  
  public static final BorkedJoystick leftStick = new BorkedJoystick(Constants.leftJoystickPort.getInt());
  public static final Joystick rightStick = new Joystick(Constants.rightJoystickPort.getInt());
  public static final OperatorJoystick operatorJoystick = new OperatorJoystick(Constants.gamepadPort.getInt());
  public static final AutoModeSelector ams = new AutoModeSelector();

  public static final Solenoid settler = new Solenoid(Constants.settlerSolenoidPort.getInt());
  public static final Solenoid popUpPistion = settler;
  
  // Controllers
  public static MultiLooper subsystemUpdater100Hz = new MultiLooper(1.0 / 100.0);
  public static TrajectoryDriveController driveController = new TrajectoryDriveController();
  public static HoldPositionController headingController = new HoldPositionController();
  public static SteerableHoldPositionController steerHeadingController = new SteerableHoldPositionController();
  public static Navigator navigator = new Navigator(drivebase);
  public static OpenLoopController openLoopShooterController = new OpenLoopController(shooter);
  public static final RpmFlywheelController shooterController = new RpmFlywheelController("ShooterController", shooter, shooter, ShooterGains.getGains()[0], 1.0/100.0);
  
  public static final BannerHotGoalDetector bannerHotGoalDetector = new BannerHotGoalDetector();
  public static final CheesyVisionHotGoalDetector visionHotGoalDetector = new CheesyVisionHotGoalDetector();
  public static final Thread hotGoalThread = new Thread(visionHotGoalDetector);
  
  public static String hotGoalDirection = "UNSURE";

  public static void initRobot() {
    // Add all subsystems to a 100Hz Looper
    subsystemUpdater100Hz.addLoopable(drivebase);
    subsystemUpdater100Hz.addLoopable(frontIntake);
    subsystemUpdater100Hz.addLoopable(rearIntake);
    subsystemUpdater100Hz.addLoopable(navigator);
    subsystemUpdater100Hz.addLoopable(pinniped);
    subsystemUpdater100Hz.addLoopable(shooter);
    
    hotGoalThread.start();
    
    compressor.start();
    shooter.useController(shooterController);
  }
}
