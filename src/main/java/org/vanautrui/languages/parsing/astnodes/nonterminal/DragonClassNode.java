package org.vanautrui.languages.parsing.astnodes.nonterminal;

import org.vanautrui.languages.lexing.tokens.ClassToken;
import org.vanautrui.languages.lexing.tokens.SymbolToken;
import org.vanautrui.languages.parsing.DragonTokenList;
import org.vanautrui.languages.parsing.IDragonASTNode;
import org.vanautrui.languages.parsing.astnodes.terminal.DragonAccessModifierNode;
import org.vanautrui.languages.parsing.astnodes.terminal.DragonIdentifierNode;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class DragonClassNode implements IDragonASTNode {

    public DragonAccessModifierNode access;

    public DragonIdentifierNode name;

    public List<DragonClassFieldNode> fieldNodeList = new ArrayList<>();

    public List<DragonMethodNode> methodNodeList = new ArrayList<>();


    public DragonClassNode(DragonTokenList tokens) throws Exception {
        System.out.println("try parse DragonClassNode");

        DragonTokenList copy = tokens.copy();

        //System.out.println(copy.toString());

        this.access = new DragonAccessModifierNode(copy);

        copy.expectAndConsumeOtherWiseThrowException(new ClassToken());

        this.name = new DragonIdentifierNode(copy);

        copy.expectAndConsumeOtherWiseThrowException(new SymbolToken("{"));

        //System.out.println(copy.toString());

        /*
        boolean success_field=true;
        while(success_field) {

            try {
                this.fieldNodeList.add(new DragonClassFieldNode(copy));
            } catch (Exception e) {
                success_field = false;
            }
        }
        //Thread.sleep(100);
        //System.out.println(copy.toString());
        boolean success_method=true;
        while(success_method) {

            try {
                this.methodNodeList.add(new DragonMethodNode(copy));
            } catch (Exception e) {
                success_method = false;
            }
        }
         */

        System.out.println("Copy :" + copy.toSourceCodeFragment());

        //i hope, that with this piece of code, the method should always be tried out first
        //because classField is a prefix of Method.
        //similar errors could maybe be fixed by just looking at the Dragon Grammar
        //and structuring the parser accordingly
        boolean success_method = true;
        boolean success_field = true;
        boolean success = true;
        while (success_field || success_method) {
            try {
                this.methodNodeList.add(new DragonMethodNode(copy));
                success_method = true;
                continue;
            } catch (Exception e) {
                success_method = false;
            }
            try {
                this.fieldNodeList.add(new DragonClassFieldNode(copy));
                success_field = true;
                continue;
            } catch (Exception e) {
                success_field = false;
            }
        }


        System.out.println("Copy :" + copy.toSourceCodeFragment());

        //System.out.println(copy.toString());

        copy.expectAndConsumeOtherWiseThrowException(new SymbolToken("}"));

        tokens.set(copy);
    }


    @Override
    public String toSourceCode() {
        String result = "";

        result += fieldNodeList.stream().map(node -> node.toSourceCode()).collect(Collectors.joining(" "));

        result += methodNodeList.stream().map(node -> node.toSourceCode()).collect(Collectors.joining(" "));

        return result;
    }
}