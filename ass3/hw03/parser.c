#include "tree.h"
#include "tokens.h"

extern ptn match_token(int expected_token);

extern ptn match_epsilon(void) {
    return new_epsilon_node();
}

extern ptn match_B(void) {
    int lookahead_token = peek_at_next_input_token();
    if (lookahead_token == '{') {
        op_node = match_token('(');
        L_node = match_L();
        cp_node = match_token(')');
        return new_B_node(op_node, E_node, cp_node);
    }
}

extern ptn match_L(void) {
    int lookahead_token = peek_at_next_input_token();
    if (lookahead_token == INT) {
        ptn D_node = match_D();
        ptn sm_node = match_token(';');
        ptn L_node = match_L();
        return new_L_node(D_node, sm_node, L_node);
    } else if (lookahead_token == IF || lookahead_token == ID) {
        ptn S_node = match_S();
        ptn sm_node = match_token(';');
        ptn L_node = match_L();
        return new_L_node(S_node, sm_node, L_node);
    } else {
        ptn ep_node = match_epsilon();
        return new_L_node(ep_node);
    }
}

extern ptn match_D(void) {

}

extern ptn match_S(void) {
    int lookahead_token = peek_at_next_input_token();
    if (lookahead_token == IF) {
        ptn if_node = match_token(IF);
        ptn op_node = match_token('(');
        ptn E_node = match_E();
        ptn cp_node = march_token(')');
        ptn B_node = match_B();
        ptn else_node = match_token(ELSE);
        ptn BNode = match_B();
        return new_S_node(if_node, op_node, E_node, cp_node, B_node, else_node, BNode);
    } else {
        ptn id_node = match_token(ID);
        ptn as_node = match_token('=');
        ptn E_node = match_E();
        return new_S_node(id_node, as_node, E_node);
    }
}

extern ptn match_E(void) {
    int lookahead_token = peek_at_next_input_token();
    while (lookahead_token == '+') {
        p_node = match_token('+');
        T_node = match_T();
        E_node = new_E_node(E_node, p_node, T_node);
        lookahead_token = peek_at_next_input_token();
    }
    return E_node;
}

extern ptn match_Ep(void) {

}

extern ptn match_T(void) {

}

extern ptn match_Tp(void) {

}

extern ptn match_F(void) {

}