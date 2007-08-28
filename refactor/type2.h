/*
 * (C) Copyright 2001 Diomidis Spinellis.
 *
 * The derived types of the type-system structure
 * Tsu (struct/union) depends on Stab which depends on Type, so we
 * split the type file into two.
 *
 * $Id: type2.h,v 1.27 2007/08/28 15:26:39 dds Exp $
 */

#ifndef TYPE2_
#define TYPE2_

// Array of ...
class Tarray: public QType_node {
private:
	Type of;
	CTConst nelem;
public:
	Tarray(Type t, CTConst n = CTConst(), qualifiers_t q = q_none) : QType_node(q), of(t), nelem(n) {}
	virtual ~Tarray() {}
	Type clone() const { return Type(new Tarray(of.clone(), nelem, get_qualifiers())); }
	Type deref() const { return of; }
	Type subscript() const { return of; }
	CTConst get_nelem() const { return nelem; }
	bool is_ptr() const { return true; }
	bool is_array() const { return true; }
	void print(ostream &o) const;
	void set_abstract(Type t);
	void set_storage_class(Type t) { of.set_storage_class(t); }
	void clear_storage_class() { of.clear_storage_class(); }
	enum e_storage_class get_storage_class() const {return of.get_storage_class(); }
	Type merge(Tbasic *b);
};

// Pointer to ...
class Tpointer: public QType_node {
private:
	Type to;
public:
	Tpointer(Type t, qualifiers_t q = q_none) :  QType_node(q), to(t) {}
	virtual ~Tpointer() {}
	Type clone() const { return Type(new Tpointer(to.clone(), get_qualifiers())); }
	Type deref() const { return to; }
	Type subscript() const { return to; }
	bool is_ptr() const { return true; }
	Type call() const { return to.call(); }
	void set_storage_class(Type t) { to.set_storage_class(t); }
	void clear_storage_class() { to.clear_storage_class(); }
	enum e_storage_class get_storage_class() const {return to.get_storage_class(); }
	void print(ostream &o) const;
	void set_abstract(Type t);
	int get_nparam() const { return to.get_nparam(); }
	Type merge(Tbasic *b);
};

// Function returning ...
class Tfunction: public Type_node {
private:
	Type returning;
	int nparam;		// Number of parameters
public:
	Tfunction(Type t, int n) : returning(t), nparam(n) {}
	virtual ~Tfunction() {}
	Type clone() const { return Type(new Tfunction(returning.clone(), nparam)); }
	Type call() const { return returning; }
	// Common extension: dereferencing a function yields a function
	Type deref() const { return clone(); }
	bool is_function() const { return true; }
	void print(ostream &o) const;
	void set_abstract(Type t);
	void set_storage_class(Type t) { returning.set_storage_class(t); }
	void clear_storage_class() { returning.clear_storage_class(); }
	enum e_storage_class get_storage_class() const {return returning.get_storage_class(); }
	void add_qualifiers(Type t) { returning.add_qualifiers(t); }
	bool qualified_const() const { return returning.qualified_const(); }
	bool qualified_restrict() const { return returning.qualified_restrict(); }
	bool qualified_volatile() const { return returning.qualified_volatile(); }
	bool qualified_unused() const { return returning.qualified_unused(); }
	qualifiers_t get_qualifiers() const { return returning.get_qualifiers(); }
	int get_nparam() const { return nparam; }
};

// Enumeration
class Tenum: public QType_node {
private:
	Tstorage sclass;
public:
	Tenum(enum e_storage_class sc = c_unspecified, qualifiers_t q = q_none) :
		 QType_node(q), sclass(sc) {}
	Type clone() const { return Type(new Tenum(sclass.get_storage_class(), get_qualifiers()));}
	void print(ostream &o) const;
	enum e_storage_class get_storage_class() const { return sclass.get_storage_class(); }
	void set_storage_class(Type t) { sclass.set_storage_class(t); };
	void clear_storage_class() { sclass.clear_storage_class(); }
	Type merge(Tbasic *b);
};

class Stab;

// Structure or Union
class Tsu: public QType_node {
private:
	Stab members_by_name;
	vector <Id> members_by_ordinal;
	Type default_specifier;	// Used while declaring a series of members
	Tstorage sclass;
public:
	Tsu(const Token &tok, const Type &typ, const Type &spec) {
		tok.set_ec_attribute(is_sumember);
		if (DP()) cout << "Adding member " << tok << "\n";
		members_by_name.define(tok, typ);
		members_by_ordinal.push_back(Id(tok, typ));
		default_specifier = spec;
	}
	Tsu(const Stab &mbn, const vector <Id> &mbo, Type ds, enum e_storage_class sc, qualifiers_t q) :
			 QType_node(q),
			 members_by_name(mbn),
			members_by_ordinal(mbo),
			default_specifier(ds),
			sclass(sc)
			{}
	Tsu(const Type &spec) { default_specifier = spec; }
	Tsu() {}
	virtual ~Tsu() {}
	bool is_su() const { return true; }
	Type clone() const { return Type(new Tsu(members_by_name, members_by_ordinal, default_specifier.clone(), sclass.get_storage_class(), get_qualifiers())); }
	void add_member(const Token &tok, const Type &typ) {
		if (DP()) cout << "Adding member " << tok << "\n";
		tok.set_ec_attribute(is_sumember);
		members_by_name.define(tok, typ);
		members_by_ordinal.push_back(Id(tok, typ));
	}
	Type get_default_specifier() const { return default_specifier; }
	void merge_with(Type t) {
		members_by_name.merge_with(t.get_members_by_name());
		const vector <Id> &m2 = t.get_members_by_ordinal();
		members_by_ordinal.insert(members_by_ordinal.end(), m2.begin(), m2.end());
	}
	Id const* member(const string& s) const
		{ return members_by_name.lookup(s); }
	Id const* member(unsigned n) const {
		if (n >= members_by_ordinal.size())
			return NULL;
		else
			return &(members_by_ordinal[n]);
	}
	const Stab& get_members_by_name() const { return members_by_name; }
	const vector <Id>& get_members_by_ordinal() const { return members_by_ordinal; }
	void print(ostream &o) const;
	enum e_storage_class get_storage_class() const { return sclass.get_storage_class(); }
	void set_storage_class(Type t) { sclass.set_storage_class(t); };
	void clear_storage_class() { sclass.clear_storage_class(); }
	Type merge(Tbasic *b);
};
//
// Incomplete structure or union reference
class Tincomplete: public QType_node {
private:
	Ctoken t;
	Tstorage sclass;
	int scope_level;		// Level to lookup for complete definitions
public:
	Tincomplete(const Ctoken& tok, int l) : t(tok), scope_level(l) {}
	Tincomplete(const Ctoken& tok, enum e_storage_class sc, int l, qualifiers_t q) :
		QType_node(q),
		t(tok),
		sclass(sc),
		scope_level(l)
		{}
	virtual ~Tincomplete() {}
	Type clone() const { return Type(new Tincomplete(t, sclass.get_storage_class(), scope_level, get_qualifiers())); }
	Id const* member(const string& s) const;
	void print(ostream &o) const;
	const Ctoken& get_token() const { return t; }
	enum e_storage_class get_storage_class() const { return sclass.get_storage_class(); }
	void set_storage_class(Type t) { sclass.set_storage_class(t); };
	void clear_storage_class() { sclass.clear_storage_class(); }
	bool is_incomplete() const { return true; }
	Type merge(Tbasic *b);
};


// Identifier; not really a type, it is returned by the lexical analyser
// It is also the type used to represent undeclared identifiers
class Tidentifier: public Type_node {
private:
	Ctoken t;
	Type of;			// Identifying a given type
public:
	Tidentifier(const Ctoken& tok) : t(tok), of(basic()) {}
	Tidentifier(const Ctoken& tok, Type typ) : t(tok), of(typ) {}
	virtual ~Tidentifier() {}
	Type clone() const { return Type(new Tidentifier(t, of.clone())); }
	const Ctoken& get_token() const { return t; }
	bool is_identifier() const { return (true); }
	const string& get_name() const { return t.get_name(); }
	Type type(Type dflt) const { return of; }
	Id const* member(const string& s) const
		{ return of.member(s); }
	Id const* member(unsigned n) const
		{ return of.member(n); }
	Type call() const;			// Function (undeclared)
	void print(ostream &o) const;
	void set_abstract(Type t);
	void set_storage_class(Type t) { of.set_storage_class(t); }
	void clear_storage_class() { of.clear_storage_class(); }
	enum e_storage_class get_storage_class() const {return of.get_storage_class(); }
	void add_qualifiers(Type t) { of.add_qualifiers(t); }
	bool qualified_const() const { return of.qualified_const(); }
	bool qualified_restrict() const { return of.qualified_restrict(); }
	bool qualified_volatile() const { return of.qualified_volatile(); }
	bool qualified_unused() const { return of.qualified_unused(); }
	qualifiers_t get_qualifiers() const { return of.get_qualifiers(); }
};

// Goto label
class Tlabel: public Type_node {
public:
	Tlabel() {}
	void print(ostream &o) const;
};

// Parameter list
class Tplist: public Type_node {
private:
	int nparam;
public:
	Tplist(int n) : nparam(n) {}
	int get_nparam() const { return nparam; }
	void add_param() { nparam++; }
	void print(ostream &o) const;
};

#endif // TYPE2_
