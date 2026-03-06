class IAttributeable {
public:
	virtual void OnAttributeChange(const Attrib::Collection*, unsigned int);
	virtual void _dtor();
};