#pragma once
#pragma warning( disable: 4267 )
#pragma warning( disable: 4996 )
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))


//#include "Controller.h"
#include <vector>
#include <cmath>
#include <cstdio>
#include <regex>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>
#include <iostream>

struct expression{
  std::string input_string;
  double list_of_digitals[256];
  int size_f_list;
  int size_d_list;
  int f_index;
  double temp_stack[256];
  int temp_index;
};

struct operator_s{
  std::string stack;
  std::string temp;
  std::string functions;
  int funct_indx;
  int temp_indx;
  int stack_indx;
  char ch;
  bool status;
  int is_func;
  int br_couter;
  bool is_start_func;
};


enum class sign{
  MINUS = 2,
  PLUS = 1,
  NONE = 0
};

struct credit_data{
  bool is_data_entred;
  std::string sum;
  std::string term;
  std::string rate;
  double au_result;
  double df_result;
};

struct inpt_text{
  std::string text {};
  std::string outpt_text {};
  std::string x {};
  std::string temp {};
  int curr_scale;
  int length;
  int breaker_counter;
  std::string cur_ch;
  bool is_x;
  bool is_x_entred;
  bool is_funct;
  bool is_credit_correct;
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  credit_data credit;
};

struct credit_report{
  int term;
  int month;
  double sum;
  double rate;
  char total_credit[300];
  char total_overpayment[300];
  char total_month_pay[1000][300];
  char loan_balance[1000][300];
  char month_pay[1000][300];
  char au_month_pay[300];
  char au_total_overpayment[300];
  char au_total_credit[300];
};

namespace s21 {

//class Controller;

class Model {

struct draw_scale{
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double total_x;
  double total_y;
  double step_x;
  double step_y;
  int x_zero;
  int y_zero;
};

 private:
 inpt_text in_text;
 draw_scale draw_sc;
 credit_report report;
 bool view_present;
 double f_x[2000];

//  Controller* controller;


  /*--------------------------------------Model_func--------------------------------------*/
  void opz_calculator(expression* expr);
  void put_num_in_temp(expression* expr, char ch);
  void calculate(expression* expr, char operator_);
  double function_calculate(double x, char fn);
  double digits_calculate(double x, double y, char operator_);
  void add_result_double_to_temp(expression* expr, double digit);


  /*------------------------------------- Model_validator---------------------------------*/
  void check_func_name(std::string& text);
  bool check_str_for_reg(std::string& temp, std::string& func_temp, std::string& text);
  bool is_first_last_ch_correct(std::string& text);
  int check_breaker(std::string& text);
  void set_x_to_temp_number_for_check(std::string& text);
  void change_funct_to_F(std::string& dst, std::string& src);
  void calc_exponential(std::string& str);
  bool chek_exp_digits(std::string& str, const std::string& template_);

  /*--------------------------------------Model_calculator---------------------------------*/
  bool de_validator(std::string& num);
  bool cr_validator(std::string& num);
  bool cr_value_validator(credit_report report);
  void zero_remover(std::string& src);
  inline int get_scale() {
    return in_text.curr_scale;
  }
  void destroy();
  std::string x_request();
  std::string calculate_x();

  void write_button_instruct(std::string ch);
  std::string& set_x_before_calculate(std::string& text, std::string& x);
  inpt_text text_size(inpt_text itd);
  inpt_text split_text(inpt_text itd, int set);
  inpt_text put_ch_to_text(std::string& ch);
  inpt_text remove_last_ch_from_text();
  void set_max_min_scale_fun(std::string& text, char ch);
  void reset_after_answer(std::string& answer);
  double get_y_coor(double y, draw_scale draw_sc);

  credit_data credit_init();

  /*----------------------------------Credit_calc--------------------------------*/
  int get_month();
  int day_in_month(int x);
  /*---------------------------------Model_input_cleaner--------------------------*/
  void init_expression(expression* src);
  void copy_str_without_spaces(std::string& dst, std::string& src, const char *symbls);
  sign is_sign(char ch);
  char get_sign_char(sign signf);
  void remove_plus_at_start_in_string(expression* expr);
  void put_zero_to_digit_list_all_elem(double *array);
  /*----------------------------------Model_parser----------------------------------*/
  void get_funct_type(expression* expr, int index);
  void remove_extra_F(expression* expr);
  inline bool is_char_equal(char ch, std::string& content) {
    return content.find(ch) != std::string::npos;
  }
  void copy_array_part(std::string& dst, std::string& src, int start_index);
  void print_exp(expression expr);
  void remove_all_numbers_from_str(expression* expr, std::string& extra);
  void set_unarn_sign(expression* expr);
  char set_funct(int index);
  /*------------------------------------Model_converter------------------------------*/
  operator_s sort_operator(operator_s op);
  operator_s create_operator(expression* expr);
  int get_priority(char ch);
  operator_s put_from_stack_to_temp(operator_s op);
  operator_s put_current_ch_to_stack(operator_s op);
  operator_s put_to_temp_breaker(operator_s op);
  operator_s check_operator(operator_s op);
  void str_num_to_digital(expression* expr, const char *str_num);

 public:
//  Model(Controller *c) : controller(c) {controller->model = this;}
//    Model(){
//        init_text_data();
//        draw_sc_init();
//    }

  std::string button_execute(std::string data, std::string input);
  std::vector<double> make_function_graph(std::string inp);
  std::vector<double> getF_X();
  draw_scale draw_sc_init();
  void init_text_data();
  std::string when_button_is_end_of_input();

  /*----------------------------------for tests------------------------------------*/
  bool validator(std::string& text);
  void smart_calc(expression* expr, std::string& input_string);
  void create_expression(expression* expr_r, std::string& src);
  void parsing(expression* expr);
  void polish_converter(expression* expr);

  void get_functions(expression* expr);
  void get_numbers(expression* expr);
  void input_string_cleaner(expression* expr);

  double double_calc(double x, double y, char operator_);
  void sign_cleaner(expression* expr);
  sign set_sign(sign current_sign, sign prv_sign);
  void space_remover(expression* expr);
  credit_report report_init(credit_data credit);
  credit_report differ_credit_calc(credit_report report);
  credit_report annuity_credit_calc(credit_report report);
  inpt_text credit_calculator(inpt_text in_text);
  credit_data add_credit(std::string& text);
  inpt_text remove_all_text();
};

}  // namespace s21
