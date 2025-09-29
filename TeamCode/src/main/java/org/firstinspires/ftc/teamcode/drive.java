package org.firstinspires.ftc.teamcode;




//import com.qualcomm.robotcore.eventloop.opmode.Disabled;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.eventloop.opmode.TeleOp;
import com.qualcomm.robotcore.hardware.DcMotor;
//import com.qualcomm.robotcore.hardware.DcMotorSimple;
import com.qualcomm.robotcore.util.ElapsedTime;
import com.qualcomm.robotcore.util.Range;




@TeleOp(name="Basic: Linear OpMode", group="Linear OpMode")
//@Disabled
public class drive extends LinearOpMode {
    private ElapsedTime runtime = new ElapsedTime();
    private DcMotor leftDrive = null;
    private DcMotor rightDrive = null;




    @Override
    public void runOpMode() {
        telemetry.addData("Status","Initialized");
        telemetry.update();




        leftDrive = hardwareMap.get(DcMotor.class, "driveL");
        rightDrive = hardwareMap.get(DcMotor.class, "driveR");




        leftDrive.setDirection(DcMotor.Direction.FORWARD);
        rightDrive.setDirection(DcMotor.Direction.FORWARD);




        waitForStart();
        runtime.reset();




        while (opModeIsActive()) {
            double leftPower;
            double rightPower;




            double drive = gamepad1.left_stick_y*0.69;
            double turn = -gamepad1.right_stick_x*0.69;
            leftPower = Range.clip(drive + turn, -1.0, 1.0) ;
            rightPower = Range.clip(drive - turn, -1.0, 1.0) ;




            leftDrive.setPower(leftPower);
            rightDrive.setPower(rightPower);




            telemetry.addData("Status", "Run Time: " + runtime.toString());
            telemetry.addData("Motors", "left (%.2f), right (%.2f)", leftPower, rightPower);
            telemetry.update();
        }
    }




}