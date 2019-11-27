package org.vanautrui.languages.commandline;

import org.apache.commons.cli.*;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;
import org.vanautrui.languages.compiler.parsing.astnodes.nonterminal.upperscopes.AST;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;

import static java.lang.System.currentTimeMillis;
import static org.vanautrui.languages.commandline.CompilerPhaseUtils.printBuildConclusion;
import static org.vanautrui.languages.commandline.CompilerPhaseUtils.printDurationFeedback;

public final class dragonc {
    //this should be the compiler

    //one thing to note would be that
    //we can include multiple stages of tokenization
    //and parsing.
    //parsing can include multiple passes and also
    //the AST and related data could undergo multiple representations
    //before reaching the final representation
    //from which code can be generated

    public static void compile_main(List<String> args) throws Exception {
        //Apache  CLI tools is just AWESOME!!
        Options options = createOptions();

        CommandLineParser parser = new DefaultParser();
        CommandLine cmd = parser.parse(options, args.toArray(new String[]{}));

        //as no option currently has an argument,
        //this simplifies the usage of the compiler
        //also, everything that doesnt start with '-' is either a source file or directory

        if(cmd.hasOption("help")){
            printHelp();
        }else {

            if(cmd.hasOption("clean")){
                if(cmd.hasOption("debug")){
                    System.out.println("clearing the cache");
                }
                final String cache_dir=System.getProperty("user.home")+"/dragoncache";
                FileUtils.deleteDirectory(Paths.get(cache_dir).toFile());
            }

            List<String> fileArgs = args.stream().filter(str -> !str.startsWith("-")).collect(Collectors.toList());

            compile_main_inner(getAllDragonFilesRecursively(fileArgs), cmd);
        }
    }

    private static List<File> getAllDragonFilesRecursively(List<String> fileArgs)throws Exception{
        //from dgc options, this can either be files or directories
        //which must be compiled together.
        List<File> results=new ArrayList<>();
        for(String s : fileArgs) {
            Path path = Paths.get(s);
            if(path.toFile().isDirectory()) {
                //add all the files recursively
                Collection<File> files = FileUtils.listFiles(
                        path.toFile(),
                        new String[]{"dg"},
                        true
                );
                results.addAll(files);
            }else {
                if (s.endsWith(".dg")) {
                    results.add(path.toFile());
                }
            }
        }
        if(results.size()==0){
            //use stdin to receive codes
            //if no files or directories are given as arguments
            //(unix philosophy)
            //throw new Exception("could not find any files with '.dg' extension.");
            //results.add(Paths.get("/dev/stdin").toFile());
        }
        return results;
    }

    public static void printHelp(){
        Options options = createOptions();
        HelpFormatter help = new HelpFormatter();
        StringBuilder sbh = new StringBuilder("");
        StringBuilder sbf = new StringBuilder("");

        sbh.append("\ndraco - a compiler for the dragon language\n");

        sbf.append("\n");
        sbf.append("EXAMPLES\n\n");
        sbf.append("    draco Main.dg\n");
        sbf.append("    draco -debug -ast Main.dg\n");
        sbf.append("\n");


        sbf.append("GITHUB");
        sbf.append("    https://github.com/pointbazaar/dragon/\n");
        sbf.append("\n");

        sbf.append("AUTHOR\n\n");
        sbf.append(
                String.format("    %-20s\n","alex23667@gmail.com")+
                String.format("    %-20s\n","David.Milosevic@web.de")
        );
        sbf.append("\n");

        sbf.append("REPORTING BUGS");
        sbf.append("    https://github.com/pointbazaar/dragon/issues\n\n");

        String header=sbh.toString();
        String footer=sbf.toString();
        help.printHelp("draco FILE...",header,options,footer,true);
    }

    //declaring these identifiers so that we can change the actual names of the options
    //without having to comb through all the code
    public static final String FLAG_DEBUG="debug";
    public static final String FLAG_TIMED="timed";

    public static final String FLAG_PRINT_SYMBOLTABLES="symboltables";
    public static final String FLAG_PRINT_HELP="help";

    public static final String FLAG_CLEAN="clean";

    private static Options createOptions(){
        //https://commons.apache.org/proper/commons-cli/usage.html

        Options opts = new Options();

        opts.addOption(new Option(FLAG_DEBUG,false,"prints debug output"));

        opts.addOption(new Option(FLAG_TIMED,false,"how long did the build take?"));

        opts.addOption(new Option(FLAG_PRINT_SYMBOLTABLES,false,"print symbol tables"));
        opts.addOption(new Option(FLAG_PRINT_HELP,false,"print help"));

        opts.addOption(new Option(FLAG_CLEAN,false,"clear cache"));

        OptionGroup optGroup = new OptionGroup();

        opts.addOptionGroup(optGroup);
        return opts;
    }

    private static void compile_main_inner(List<File> sources,CommandLine cmd){

        boolean debug=cmd.hasOption(FLAG_DEBUG);
        boolean timed=cmd.hasOption(FLAG_TIMED);

        long start_time_ms = currentTimeMillis();

        try {
            final List<String> codes=new ArrayList<String>();

            for(File file : sources){
                String sourceCode = new String(Files.readAllBytes(file.toPath()));
                codes.add(sourceCode);
                if(debug) {
                    System.out.println(sourceCode);
                }
            }

            final CompilerPhases phases = new CompilerPhases(cmd);
            final ParserPhases pphases = new ParserPhases();

            //PHASE PREPROCESSOR (processes 'use' directive), PHASE CLEAN, PHASE LEXING, PHASE PARSING

            final List<AST> asts = pphases.phase_preprocessor_and_clean_and_lexing_and_parsing(sources);

            //PHASE TYPE CHECKING
            phases.phase_typecheck(asts);

            //PHASE CODE GENERATION, returns a list of paths where the files for the subroutines are
            final List<Path> vm_code_files = phases.phase_vm_codegeneration(asts, cmd.hasOption(FLAG_PRINT_SYMBOLTABLES));

            //PHASE VM CODE COMPILATION, PHASE GENERATE EXECUTABLE
            //this phase depends on 'dracovm'
            //which can be obtained here: https://github.com/pointbazaar/dracovm-compiler
            //for each subroutine in vm code, make a NAME.subroutine.dracovm file
            final String call = "dracovm "+vm_code_files.stream().map(path->path.toString()).collect(Collectors.joining(" "));
            System.out.println(call);

            final Process process = Runtime.getRuntime().exec(call);
            process.waitFor();
            final String output = IOUtils.toString(process.getInputStream());
            System.out.println(output);
            final String output2 = IOUtils.toString(process.getErrorStream());
            System.out.println(output2);

            long end_time_ms = currentTimeMillis();
            long duration = end_time_ms-start_time_ms;

            //https://www.utf8icons.com/
            if(timed) {
                printDurationFeedback(duration);
            }
            {
                printBuildConclusion(true);
            }

        } catch (Exception e) {

            System.err.println(e.getMessage());
            e.printStackTrace();
            printBuildConclusion(false);
        }
    }
}
