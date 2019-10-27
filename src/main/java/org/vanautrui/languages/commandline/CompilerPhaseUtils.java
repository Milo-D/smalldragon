package org.vanautrui.languages.commandline;

import org.vanautrui.languages.CompilerApp;

public class CompilerPhaseUtils {
    static void printBeginPhase(String phaseName, boolean debug) {
        if(debug) {
            System.out.println(phaseName);
        }
    }

    static void printEndPhase(boolean success, boolean debug) {

        if(debug) {
            System.out.println((success)?"✓":"⚠");
        }
    }
    static void printBuildConclusion(boolean success){
        if(success) {
            System.out.println("BUILD SUCCESS");
        }else {
            System.out.println("BUILD FAILURE");
        }
    }

    public static void printDuration(long start,long end){
        long duration=end-start;
        System.out.println(String.format("Duration: %6sms",duration));
    }

    static void printDurationFeedback(long duration /*milliseconds*/){
        final String str = duration + " ms";
        if(duration>500) {
            CompilerApp.println("☠ "+str+" Compilation took too long. This needs to be fixed. Please file an Issue on GitHub.");
        }else if(duration>200) {
            CompilerApp.println("☠ "+str+" we are truly sorry for the delay :(");
        }else if(duration>100){
            CompilerApp.println("✝ "+str+" sorry it took so long!");
        }else {
            CompilerApp.println("☕ " + str);
        }
    }
}
