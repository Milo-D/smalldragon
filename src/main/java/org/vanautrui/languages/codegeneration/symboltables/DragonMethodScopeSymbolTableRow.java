package org.vanautrui.languages.codegeneration.symboltables;

public class DragonMethodScopeSymbolTableRow {

    public final String varName;
    public final String typeName;
    public final int index;

    public DragonMethodScopeSymbolTableRow(int index,String varName, String typeName){
        this.index=index;
        this.typeName=typeName;
        this.varName=varName;
    }
}
