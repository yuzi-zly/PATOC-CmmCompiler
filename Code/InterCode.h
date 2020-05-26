//三个计数器 变量个数，临时变量个数，标签个数
//lookup用来从符号表里查询变量的类型，如果是基本的数据类型，并不需要查询符号表，应该查询是否之前已经使用过该变量，返回一个操作数

typedef struct Operand_* Operand;
struct Operand_{
    enum{Ope_NONE, Ope_VAR, Ope_TVAR, Ope_INT, Ope_ADDR, Ope_FUNC, Ope_LAB} kind;
    union 
    {
       int var_no;
       int tvar_no;
       int const_int;
       char* funcname;
       int lab_no;
    } u;
    enum{ADDR_VAR,ADDR_TVAR} addr;
    bool is_addr;
};

struct InterCode
{
    enum {IC_LAB, IC_FUNC, IC_ASSIGN, IC_ADD, IC_SUB, IC_MUL, IC_DIV, IC_TAKEADDR, IC_PARSEADDRR,IC_PARSEADDRL,
     IC_RELOP, IC_GOTO, IC_IFGOTO,  IC_RETURN, IC_DEC, IC_ARG, IC_CALL, IC_PARAM, IC_READ, IC_WRITE,IC_SPACELINE} IC_type;
    union 
    {
        struct {Operand label; } ic_lab;
        struct {Operand function; } ic_func;
        struct {Operand right, left; } ic_assign;
        struct {Operand right1, right2, left; } ic_add;
        struct {Operand right1, right2, left; } ic_sub;
        struct {Operand right1, right2, left; } ic_mul;
        struct {Operand right1, right2, left; } ic_div;
        //struct {Operand right, left; } ic_takeaddr;
        //struct {Operand right, left; } ic_parseaddrr;//取右边地址
        //struct {Operand right, left; } ic_parseaddrl;//取左边地址
        struct {Operand right, left; char* relop; } ic_relop;
        //struct {Operand right, binop, left; } ic_binop;
        struct {Operand label; } ic_goto;
        struct {struct InterCode* relop; Operand label; } ic_ifgoto;
        struct {Operand ret; } ic_return;
        struct {Operand var; int size; } ic_dec;
        struct {Operand arg; } ic_arg;
        struct {Operand left, function; } ic_call;
        struct {Operand param; } ic_param;
        struct {Operand read_var; } ic_read;
        struct {Operand write_var; } ic_write;
    } u;      
};

struct InterCodes {
    struct InterCode* code;
    struct InterCodes* next, *prev;
};

Operand CreateOperand(int kind);
int CalculateSize(Type type);

void CreateAndAddFunctionIC(char* funcname);
void CreateAndAddParamIC(Item* funcitem);
void CreateAndAddDecIC(int var_no, Type this_type);
void CreateAndAddAssignIC(Operand left, Operand right);
void CreateAndAddAddIC(Operand left,Operand right1, Operand right2);
void CreateAndAddSubIC(Operand left,Operand right1,Operand right2);
void CreateAndAddMulIC(Operand left,Operand right1, Operand right2);
void CreateAndAddDivIC(Operand left,Operand right1, Operand right2);
void CreateAndAddLabelIC(int label);
struct InterCode* CreateRelopIC(Operand left, Operand right, char* op);
void CreateAndAddIfIC(struct InterCode* relop, int label);
void CreateAndAddGotoIC(int label);
void CreateAndAddReadIC(Operand read_var);
void CreateAndAddCallIC(Operand left, char* funcname);
void CreateAndAddWriteIC(Operand write_var);
void CreateAndAddArgIC(Operand arg_var);
void CreateAndAddReturnIC(Operand ret_var);
void CreateAndAddSpacelineIC();
void PrintInterCodes(char* filename);
char* PrintEachInterCode(struct InterCode* code);
char* getcode(Operand op);