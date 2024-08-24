#include "PTML_VARS.h"
#include "PTML_shared_headers.h"

void PTML::SET()
{
	ARGC(2);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), STR(2));
}

void PTML::VARS()
{
	ARGC(0);
	t_list<t_string> vars;
	for (auto& var : ptm->get_vars())
		vars.push_back(t_string::fmt("%s: %s", var.first.c_str(), var.second.c_str()));
	for (auto& tbl : ptm->get_tables())
		vars.push_back(t_string::fmt("%s[%i,%i]", 
			tbl.first.c_str(), tbl.second.get_cols(), tbl.second.get_rows()));

	PRINT_LIST(vars);
}

void PTML::SWAP()
{
	ARGC(2);
	REQUIRE_IDENT(1);
	REQUIRE_IDENT(2);
	const t_string&& val1 = STR(1);
	const t_string&& val2 = STR(2);
	ptm->set_var(IDENT(1), val2);
	ptm->set_var(IDENT(2), val1);
}

void PTML::MEM_CLR()
{
	ARGC(0);
	ptm->delete_all_vars();
	ptm->delete_all_tables();
}

void PTML::TBL_NEW()
{
	ARGC(3);
	REQUIRE_IDENT(1);
	ptm->create_table(IDENT(1), NUM(2), NUM(3));
}

void PTML::TBL_SET()
{
	ARGC(4);
	REQUIRE_IDENT(1);
	auto& name = IDENT(1);

	if (!ptm->has_table(name)) {
		error = err.table_not_found;
		return;
	}

	auto& tbl = ptm->get_table(name);

	int col = NUM(2);
	int row = NUM(3);
	CHK_TBL_BOUNDS(tbl, col, row);

	tbl.set(col, row, STR(4));
}

void PTML::TBL_GET()
{
	ARGC(4);
	REQUIRE_IDENT(1);
	REQUIRE_IDENT(4);
	auto& tbl_name = IDENT(1);
	auto& var_name = IDENT(4);

	if (!ptm->has_table(tbl_name)) {
		error = err.table_not_found;
		return;
	}

	auto& tbl = ptm->get_table(tbl_name);

	int col = NUM(2);
	int row = NUM(3);
	CHK_TBL_BOUNDS(tbl, col, row);

	ptm->set_var(var_name, tbl.get(col, row));
}
