package org.firstinspires.ftc.teamcode;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.eventloop.opmode.TeleOp;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.util.Range;
import com.qualcomm.robotcore.hardwareMap;
import com.qualcomm.robotcore.digital;

@TeleOp(name="Basic: Linear OpMode", group="Linear OpMode")
public class shooter extends LinearOpMode {
    private DcMotor shooter = null;

    @Override
    public void runShooter() {
        telemetry.addData("Shooter Status", "Initialized");
        telemetry.update();

        shooter = hard
    }
}