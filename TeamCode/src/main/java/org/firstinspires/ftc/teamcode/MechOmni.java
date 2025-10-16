package org.firstinspires.ftc.teamcode;




//import com.qualcomm.robotcore.eventloop.opmode.Disabled;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.eventloop.opmode.TeleOp;
import com.qualcomm.robotcore.hardware.CRServo;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.util.ElapsedTime;
import com.qualcomm.robotcore.util.Range;


@TeleOp(name="Basic: Linear OpMode (MechOmni)", group="Linear OpMode")
//@Disabled
public class MechOmni extends LinearOpMode {
    private ElapsedTime runtime = new ElapsedTime();
    private DcMotor leftDrive = null;
    private DcMotor rightDrive = null;

    private DcMotor shooter = null;

    private CRServo lServo = null;
    private CRServo rServo = null;


    @Override
    public void runOpMode() {
        telemetry.addData("Status","Initialized");
        telemetry.update();




        leftDrive = hardwareMap.get(DcMotor.class, "driveL");
        rightDrive = hardwareMap.get(DcMotor.class, "driveR");
        shooter = hardwareMap.get(DcMotor.class, "shooter");
        lServo = hardwareMap.get(CRServo.class, "lServo");
        rServo = hardwareMap.get(CRServo.class, "rServo");



        leftDrive.setDirection(DcMotor.Direction.FORWARD);
        rightDrive.setDirection(DcMotor.Direction.FORWARD);
        shooter.setDirection(DcMotor.Direction.FORWARD);
        lServo.setDirection(CRServo.Direction.FORWARD);
        rServo.setDirection(CRServo.Direction.REVERSE);
        lServo.setPower(0.0);
        rServo.setPower(0.0);



        waitForStart();
        runtime.reset();
        double shooterPower = 0.0;



        while (opModeIsActive()) {
            double leftPower;
            double rightPower;
            double servoPower;

            boolean reverseShoot = gamepad1.right_bumper;
            boolean slowshoot = gamepad1.y;
            boolean sShoot = gamepad1.x;
            boolean servo = gamepad1.a;
            boolean revservo = gamepad1.b;
            double drive = gamepad1.left_stick_y*0.69;
            double turn = -gamepad1.right_stick_x*0.69;
            double ltrig = gamepad1.right_trigger;
//            double rtrig = -gamepad1.right_trigger;

            leftPower = Range.clip(drive + turn, -1.0, 1.0) ;
            rightPower = Range.clip(drive - turn, -1.0, 1.0) ;

            if (gamepad1.dpad_up) {
                shooterPower += 0.05;
                sleep(150);
            } else if (gamepad1.dpad_down) {
                shooterPower -= 0.05;
                sleep(150);
            }

            shooterPower = Range.clip(shooterPower, -1.0, 1.0);

            leftDrive.setPower(leftPower);
            rightDrive.setPower(rightPower);
            if (ltrig<0) {
                shooter.setPower(ltrig);
            } else if (slowshoot) {
                shooter.setPower(0.1);
            } else if (sShoot) {
                shooter.setPower(shooterPower);
            } else if (reverseShoot) {
                shooter.setPower(-0.1);
            } else {
                shooter.setPower(0.0);
            }


            if (servo) {
                servoPower=1.0;
            }
            else if (revservo){
                servoPower=-1.0;
            }

            else {
                servoPower=0.0;
            }

            lServo.setPower(servoPower);
            rServo.setPower(servoPower);



            telemetry.addData("Status", "Run Time: " + runtime.toString());
            telemetry.addData("Motors", "left (%.2f), right (%.2f)", leftPower, rightPower);
            telemetry.addData("Shoot Speed", "%.2f", shooterPower);
            telemetry.update();
        }
    }




}