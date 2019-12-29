package org.vanautrui.languages.compiler.parsing.astnodes.typenodes.basic_and_wrapped;

import org.vanautrui.languages.compiler.parsing.astnodes.typenodes.TypeNode;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public final class SubroutineTypeNode implements IBasicAndWrappedTypeNode {

	public TypeNode returnType;

	public boolean hasSideEffects;

	public List<TypeNode> argumentTypes = new ArrayList<>();

	public SubroutineTypeNode(){}

	public SubroutineTypeNode(List<TypeNode> argumentTypes, final TypeNode return_type, final boolean hasSideEffects) {
		this.argumentTypes=argumentTypes;
		this.returnType = return_type;
		this.hasSideEffects = hasSideEffects;
	}


	@Override
	public String getTypeName() {
		return this.toSourceCode();
	}

	@Override
	public String toSourceCode() {
		return
				"("
						+ argumentTypes
						.stream()
						.map(TypeNode::getTypeName)
						.collect(Collectors.joining(","))
						+ ")"
						+ ((this.hasSideEffects) ? "~>" : "->")

						+ returnType.getTypeName();

	}

	@Override
	public boolean isPrimitive() {
		return false;
	}
}
