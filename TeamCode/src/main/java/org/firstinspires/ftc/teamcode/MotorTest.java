package org.firstinspires.ftc.teamcode;




//import com.qualcomm.robotcore.eventloop.opmode.Disabled;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.eventloop.opmode.TeleOp;
import com.qualcomm.robotcore.hardware.CRServo;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.util.ElapsedTime;
import com.qualcomm.robotcore.util.Range;


@TeleOp(name="MotorTest", group="Linear OpMode")
//@Disabled
public class MotorTest extends LinearOpMode {
    private ElapsedTime runtime = new ElapsedTime();
    private DcMotor driveRL = null;
    private DcMotor driveRR = null;

    private DcMotor driveFL = null;
    private DcMotor driveFR = null;


    @Override
    public void runOpMode() {
        telemetry.addData("Status","Initialized");
        telemetry.update();




        driveRL = hardwareMap.get(DcMotor.class, "driveRL");
        driveRR = hardwareMap.get(DcMotor.class, "driveRR");
        driveFL = hardwareMap.get(DcMotor.class, "driveFL");
        driveFR = hardwareMap.get(DcMotor.class, "driveFR");



//        driveRL.setDirection(DcMotor.Direction.FORWARD);
//        driveRR.setDirection(DcMotor.Direction.FORWARD);
//        driveFL.setDirection(DcMotor.Direction.FORWARD);
//        driveFR.setDirection(DcMotor.Direction.FORWARD);



        waitForStart();
        runtime.reset();


        while (opModeIsActive()) {
            if (gamepad1.left_trigger >= 0.25) {
                driveFL.setPower(1);
                sleep(1000);
                driveFL.setPower(0);
            } else if (gamepad1.right_trigger >= 0.25) {
                driveFR.setPower(1);
                sleep(1000);
                driveFR.setPower(0);
            } else if (gamepad1.left_bumper) {
                driveRL.setPower(1);
                sleep(1000);
                driveRL.setPower(0);
            } else if (gamepad1.right_bumper) {
                driveRR.setPower(1);
                sleep(1000);
                driveRR.setPower(0);
            }
        }
    }




}