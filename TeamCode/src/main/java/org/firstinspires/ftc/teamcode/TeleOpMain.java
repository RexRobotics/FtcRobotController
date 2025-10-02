package org.firstinspires.ftc.teamcode;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.eventloop.opmode.TeleOp;


@TeleOp(name="Main (Linear OpMode)", group="Linear OpMode")
public class TeleOpMain extends LinearOpMode {
    Shooter shooter;
    Drivertrain drive;
    Input input;
    @Override
    public void runOpMode() {
        telemetry.addData("Status", "Initilizing");
        telemetry.update();
        shooter = new Shooter(hardwareMap);
        drivetrain = new Drivetrain(hardwareMap);
        shooter = new Shooter(hardwareMap);
        gate = new gate(hardwareMap);

        drivetrain.init();
        shooter.init();
        gate.init();
        

        telemetry.addData("Status", "Intialized");
        telemetry.addData("READY");

        waitForStart();

        while (opModeIsActive()) {
            drivetrain.update(gamepad1);
            shooter.update(gamepad1);
            intake.update(gamepad1);

            
        }

        

    }
}