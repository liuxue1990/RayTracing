#ifndef OPERATOR_H
#define OPERATOR_H

#include "Rendering/Geometry.h" 

class Operand{
public: 
	virtual Pt3 getCenter()=0; 
	virtual void translate(const Vec3& trans)=0; 
	virtual void rotate(double d, int axis)=0; 
	virtual string toString(){
		return "Operand" + getCenter().toString();
	}
}; 

class Operator : public Geometry{
protected: 
	//it should be a list of operands instead of hard coding two, probably
	Operand* _primary; 
	Operand* _secondary; 

	int _usageSt; 
	Vec3 _dirx, _diry, _dirz; 
public: 
	Operator(Operand* op){
		_primary = op; 
		_usageSt = OP_NONE; 

		_secondary = NULL; 

		_dirx = Vec3(OP_STEP,0,0,0); 
		_diry = Vec3(0,OP_STEP,0,0); 
		_dirz = Vec3(0,0,OP_STEP,0); 
	}

	virtual void accept(GeometryVisitor* visitor, void* ret){
		visitor->visit(this, ret); 
	}

	virtual void accept(SceneObjectVisitor* visitor, void* ret) { } // not a scene object, do nothing
	
	virtual string toString(){
		return "Operator" + _primary->toString();
	}
	Operand* getPrimaryOp() { return _primary; }
	Operand* getSecondaryOp() { return _secondary; }
	void setPrimaryOp(Operand* op) { _primary = op; }
	void setSecondaryOp(Operand* op) { _secondary = op; }

	const Vec3& getDirX() { return _dirx; }
	const Vec3& getDirY() { return _diry; }
	const Vec3& getDirZ() { return _dirz; }

	void setState(int st) { _usageSt = st; }
	int getState() { return _usageSt; }
	void translate(const Vec3& v) { 
		_primary->translate(v); 
		if(_secondary)
			_secondary->translate(v); 
	}

	void rotate(double r, int axis){ 
		_primary->rotate(r,axis); 
		if(_secondary)
			_secondary->rotate(r,axis);
	}

	void updateTransform() { } 

};

#endif