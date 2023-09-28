#include "Model.h"


namespace s21 {


std::string Model::button_execute(std::string data, std::string input) {
    in_text.outpt_text = input;
//    std::cout << "line 9 : data = " << data << " input = " << input << std::endl;///
    std::string res {};
  if (data == "=") {
//        std::cout << "line 12 : in_text.is_x_entred = " << in_text.is_x_entred << std::endl;///
    if (in_text.is_x_entred) {
//        std::cout << "line 14 : gone." << std::endl;///
       res = when_button_is_end_of_input();
    }  else if (in_text.is_x) {
//        std::cout << "line 17 : gone." << std::endl;///
        res = calculate_x();
    } else if (in_text.outpt_text.find('x') != std::string::npos) {
//        std::cout << "line 20 : gone." << std::endl;///
        res = x_request();
    } else {
//        std::cout << "line 23 : gone." << std::endl;///
        res = when_button_is_end_of_input();
    }
  } else if (data == "f(x)=") {
//    std::cout << "line 27 : gone." << std::endl;///
  } else if (data == "D(f)") {
//    std::cout << "line 31 : gone." << std::endl;///
    if (de_validator(in_text.text)) {
        set_max_min_scale_fun(in_text.text, 'x');
    }
  } else if (data == "E(f)") {
//    std::cout << "line 36 : gone." << std::endl;///
        set_max_min_scale_fun(in_text.text, 'y');
  } else if (data == "Cred") {
//    std::cout << "line 39 : gone." << std::endl;///
        in_text = credit_calculator(in_text);
  } else {
        write_button_instruct(data);
        res = in_text.outpt_text.c_str();
  }
//  std::cout << "line 45 : res = " << res << std::endl;///
  return res;
}

void Model::init_text_data() {
  std::setlocale(LC_NUMERIC,"C");
  in_text.text.clear();
  in_text.outpt_text.clear();
  in_text.cur_ch.clear();
  in_text.breaker_counter = 0;
  in_text.length = 0;
  in_text.is_funct = false;
  in_text.curr_scale = 49;
  in_text.is_x = false;
  in_text.is_x_entred = false;
  in_text.x_min = -10;
  in_text.x_max = 10;
  in_text.y_min = -10;
  in_text.y_max = 10;
  in_text.is_credit_correct = false;
  in_text.credit = credit_init();
}

std::string Model::x_request() {
  std::string res {"0"};
  if (validator(in_text.outpt_text)) {
    in_text.temp = in_text.outpt_text;
    remove_all_text();
    in_text.is_x = true;
    res = "Enter x value and press =";
  }
  return res;
}

std::string Model::calculate_x() {
  when_button_is_end_of_input();
  in_text.is_x_entred = true;
  in_text.outpt_text = in_text.temp;
  if ((int)in_text.outpt_text.length() + (int)in_text.x.length() <= 255) {
      set_x_before_calculate(in_text.outpt_text, in_text.x);
  }
  in_text.text = in_text.outpt_text;
  in_text.is_x = false;
  return in_text.outpt_text;
}

std::vector<double> Model::make_function_graph(std::string inp) {
    draw_sc = draw_sc_init();
    in_text.outpt_text = inp;
//    std::cout << "Model::make_function_graph line 96 func make_function_graph, in_text.outpt_text = " << in_text.outpt_text << std::endl;///
    std::vector<double> f_y(2000);
  if (validator(in_text.outpt_text)) {
    std::string temp;
    for (int c = 0; c < 2000; c++) {
        f_y.at(c) = NAN;
    }
    double z = draw_sc.x_min;
    for (int s = 0; s < 2000; s++, z += draw_sc.step_x) {
        f_x[s] = z * 1000;
        temp = in_text.outpt_text;
//        std::cout << "Model::make_function_graph line 108: z = " << z << std::endl;///
        char num1[100];
        snprintf(num1, sizeof(char)*100, "%.15f", z);
        std::string num(num1);
//        std::cout << "Model::make_function_graph line 112: num = " << num << std::endl;///
        set_x_before_calculate(temp, num);
//        std::cout << "Model::make_function_graph line 114: temp = " << temp << std::endl;///
        expression expr;
        smart_calc(&expr, temp);
        f_y.at(s) = expr.temp_stack[0];
    }
// показать график
  }
  for (int i = 0; i < 2000; i++){

    if (f_y.at(i) >= draw_sc.y_min*1.1 && f_y.at(i) <= draw_sc.y_max*1.1) {
                      f_y.at(i) = get_y_coor(f_y.at(i), draw_sc);
                  }
//    std::cout << std::endl;///
  }
//  std::cout << "Model::make_function_graph line 129: f_y[1] = " << f_y.at(1) << " draw_sc.y_min = "  << draw_sc.y_min << ", draw_sc.y_max = " ///
//   << draw_sc.y_max << ", draw_sc.step_y = " << draw_sc.step_y << std::endl;///
//  std::cout << "Model::make_function_graph line 132: f_y.lenght = " << f_y.size() << " f_y[1] = " << f_y[1] <<  std::endl;///

  return f_y;
}

std::vector<double> Model::getF_X() {
    std::vector<double> vec(2000);
    for(int i = 0; i < 2000; i++) {
        vec.at(i) = f_x[i];
    }
    return vec;
}

double Model::get_y_coor(double y, draw_scale draw_sc) {
    double calc;
//    std::cout << "line 147: y = " << y << " y_min = " << draw_sc.y_min << " step_y = " << draw_sc.step_y << std::endl;///
    if (y < 0) {
        calc = (((y - draw_sc.y_min)*draw_sc.step_y)*-1+2000) - 1000;
    } else {
        calc = (2000-((y - draw_sc.y_min)*draw_sc.step_y)) - 1000;
    }
    return calc > 2000 ? 2000 : calc;
}

std::string Model::when_button_is_end_of_input() {
////    std::cout << "line 152 : function when_button_is_end_of_input is job." << std::endl;///
    std::string res {"0"};
  if (validator(in_text.outpt_text)) {
////  std::cout << "line 155 : gone." << std::endl;///
    char result[300];
    expression expr;
    smart_calc(&expr, in_text.outpt_text);
    snprintf(result, sizeof(char)*300, "%.6f", expr.temp_stack[0]);
    std::string s(result);
    zero_remover(s);
    if (in_text.is_x) {
        in_text.x = s;

    } else {
        res = s.c_str();
        reset_after_answer(s);
    }
  }
  return res;
}

void Model::write_button_instruct(std::string ch) {
  if (ch == "R") {
    if (in_text.length > 0) {
      in_text = remove_last_ch_from_text();
    }
    if (in_text.length == 0) {
      in_text.outpt_text.resize(1);
      in_text.outpt_text.replace(0, 1, 1, '0');
    }
  } else if (ch == "C") {
    in_text = remove_all_text();
    in_text.outpt_text.resize(1);
    in_text.outpt_text.replace(0, 1, 1, '0');
  } else {
    in_text = put_ch_to_text(ch);
  }
}

std::string& Model::set_x_before_calculate(std::string& text, std::string& x) {
  std::string temp = text;
  text.clear();
  std::size_t len = temp.length();
  int p = 0;
  for (int i = 0; i < (int)len; i++) {
      if (temp[i] == 'x') {
          text.append(x);
          p += (int)x.length();
      } else {
          text.replace(p, 1, 1, temp[i]);
          p++;
      }
  }
  return text;
}

inpt_text Model::text_size(inpt_text itd) {
  if (itd.length >= 106 && get_scale() > 22) {
      itd = split_text(itd, 45);
  } else if (itd.length > 55 && get_scale() > 27) {
      itd = split_text(itd, 27);
  } else if (itd.length > 19 && get_scale() != 47) {
      itd = split_text(itd, 19);
  } else {
      itd.outpt_text = itd.text;
  }
  return itd;
}

inpt_text Model::split_text(inpt_text itd, int set) {
  int delim = set;
  int ot = 0;
  for (int t = 0; t < itd.length; ot++) {
    if (ot != delim) {
        itd.outpt_text.replace(ot, 1, 1, itd.text[t]);
        t++;
    } else {
        delim += set;
        itd.outpt_text.replace(ot, 1, 1, '\n');
    }
  }
  itd.outpt_text.resize(ot);
  return itd;
}

void Model::reset_after_answer(std::string& answer) {
  in_text = remove_all_text();
  in_text.text = answer;
  in_text.length = (int)answer.length();
  in_text.outpt_text = answer;
  in_text.is_funct = false;
  in_text.is_x_entred = false;
  in_text.is_x = false;
  in_text.is_credit_correct = false;
}

inpt_text Model::put_ch_to_text(std::string& ch) {
  in_text.cur_ch = ch;
  int ln = 255 + (int)ch.length();
  if (in_text.length < ln) {
    in_text.text.append(ch);
    in_text.length += (int)in_text.cur_ch.length();
    in_text = text_size(in_text);
  }
  return in_text;
}

inpt_text Model::remove_last_ch_from_text() {
  if (in_text.length > 0) {
      in_text.text.resize(in_text.length - 1);
      in_text.length--;
      in_text = text_size(in_text);
  }
  return in_text;
}

inpt_text Model::remove_all_text() {
  in_text.text.clear();
  in_text.outpt_text.clear();
  in_text.x.clear();
  in_text.length = 0;
  in_text.is_x = false;
  in_text.is_funct = false;
  in_text.is_x_entred = false;
  in_text.is_credit_correct = false;
  in_text.credit = credit_init();
  return in_text;
}

void Model::set_max_min_scale_fun(std::string& text, char ch) {
  std::size_t poss = text.find("/");
  std::string first, second;
  if (poss != std::string::npos) {
    first = text.substr(0, (int)poss);
    second = text.substr((int)poss + 1);
  }
  if (!first.empty() && !second.empty()) {
    double d_first = atof(first.c_str());
    double d_second = atof(second.c_str());
    if ((d_second - d_first) >= 0 && ch == 'x') {
        in_text.x_max = d_second;
        in_text.x_min = d_first;
    } else if ((d_second - d_first) >= 0 && ch == 'y') {
        in_text.y_max = d_second;
        in_text.y_min = d_first;
    }
  }
  in_text = remove_all_text();
}

bool Model::de_validator(std::string& num) {
  std::string template_ = "^[-]{0,}[0-9]{1,10}\\/{1,}[-]{0,}[0-9]{1,10}$";
  return std::regex_match(num, std::regex(template_));
}

bool Model::cr_validator(std::string& num) {
    std::string template_ = "^[0-9]{1,15}\\/[0-9]{1,3}\\/[0-9.]{1,4}$";
  return std::regex_match(num, std::regex(template_));
}

bool Model::cr_value_validator(credit_report report) {
  bool is_correct = true;
  if (report.term <= 0 || report.term > 130 ||
      report.rate > 999 || report.rate <= 0 || report.sum <= 0) {
      is_correct = false;
  }
  return is_correct;
}

void Model::polish_converter(expression* expr) {
  operator_s op = create_operator(expr);
  std::string s1("LOINQCSTG"), s2("+-*/^#"), s3("()");
  int i = 0;
  std::size_t ln = expr->input_string.length();
  for (; i < (int)ln; i++) {
    op.ch = expr->input_string[i];
    if (op.ch == 'D') {
        op.temp.replace(op.temp_indx, 1, 1, 'D');
        op.temp_indx++;
    } else if (op.ch == 'Z') {
        op.temp.replace(op.temp_indx, 1, 1, 'Z');
        op.temp_indx++;
    } else if (is_char_equal(op.ch, s1)) {
        op.stack.replace(op.stack_indx, 1, 1, op.ch);
        op.stack_indx++;
    } else if (is_char_equal(op.ch, s2)) {
        op = check_operator(op);
    } else if (is_char_equal(op.ch, s3)) {
        op = put_to_temp_breaker(op);
    }
  }
  while (op.stack_indx > 0) {
      op = put_from_stack_to_temp(op);
  }
  expr->input_string = op.temp;
}

void Model::str_num_to_digital(expression* expr, const char *str_num) {
//  std::cout << "line 322: str_num = " << str_num << std::endl;///
  expr->list_of_digitals[expr->size_d_list] = atof(str_num);
  expr->size_d_list += 1;
}

operator_s Model::sort_operator(operator_s op) {
  int stack_op_pr = get_priority(op.stack[op.stack_indx-1]);
  int current_op_pr = get_priority(op.ch);
  if (stack_op_pr < current_op_pr) {
    op = put_current_ch_to_stack(op);
    op.status = false;
    op.ch = '\0';
  } else if (op.stack_indx > 0) {
      op = put_from_stack_to_temp(op);
  } else {
      op = put_current_ch_to_stack(op);
      op.ch = '\0';
  }
  return op;
}

operator_s Model::create_operator(expression* expr) {
  operator_s op;
  op.temp_indx = 0,
  op.stack_indx = 0,
  op.funct_indx = 0;
  op.ch = expr->input_string[0];
  op.status = true;
  op.temp.clear();
  op.stack.clear();
  op.functions.clear();
  op.is_func = 0;
  op.br_couter = 0;
  op.is_start_func = false;
  return op;
}

operator_s Model::put_from_stack_to_temp(operator_s op) {
  op.temp.replace(op.temp_indx, 1, 1, op.stack[op.stack_indx-1]);
  op.temp_indx++;
  op.stack.resize(op.stack_indx-1);
  op.stack_indx--;
  return op;
}

operator_s Model::put_to_temp_breaker(operator_s op) {
  std::string s("(");
  if (op.ch == ')') {
    op.br_couter--;
    int k = op.stack_indx-1;
    for (; k >= 0; k--) {
      if (!is_char_equal(op.stack[k], s)) {
        op = put_from_stack_to_temp(op);
      } else {
        if (op.is_func > 0 && op.br_couter < op.is_func) {
          op.stack.replace(op.stack_indx-1, 1, 1, op.functions[op.funct_indx-1]);
          op.functions.replace(op.funct_indx-1, 1, 1, '\0');
          op.funct_indx--;
          op.is_func--;
          op.br_couter = 0;
        } else {
          op.stack.resize(k);
          op.stack_indx--;
        }
        break;
      }
    }
  } else {
    if (!op.is_start_func) {
      op = put_current_ch_to_stack(op);
    } else {
      op.is_func++;
      op.stack.replace(op.stack_indx, 1, 1, op.ch);
      op.stack_indx++;
    }
    op.br_couter++;
  }
  return op;
}

operator_s Model::check_operator(operator_s op) {
  if (op.stack_indx > 0) {
    while (op.status == true && op.stack_indx > 0) {
        op = sort_operator(op);
    }
    if (op.ch) {
        op = sort_operator(op);
    }
    op.status = true;
  } else {
    op = put_current_ch_to_stack(op);
  }
  return op;
}

int Model::get_priority(char ch) {
  std::string s1("+-"), s2("*/#"), s3("^LOINQCSTG");
  int priority = 1;
  if (is_char_equal(ch, s1)) {
    priority = 2;
  } else if (is_char_equal(ch, s2)) {
    priority = 3;
  } else if (is_char_equal(ch, s3)) {
    priority = 4;
  }
  return priority;
}

operator_s Model::put_current_ch_to_stack(operator_s op) {
  if (op.stack_indx <= (int)op.stack.length()) {
    op.stack.replace(op.stack_indx, 1, 1, op.ch);
  } else {
    op.stack.append(1, op.ch);
  }
  op.stack_indx++;
  return op;
}

inpt_text Model::credit_calculator(inpt_text in_text) {
  if (cr_validator(in_text.text) == true) {
    in_text.credit = add_credit(in_text.text);
    report = report_init(in_text.credit);
    if (cr_value_validator(report)) {
      report = differ_credit_calc(report);
      report = annuity_credit_calc(report);
//      view_credit_window(report);  //  показывает кредитное окно
    }
  }
  return in_text;
}

credit_data Model::add_credit(std::string& text) {
  credit_data credit;
  std::string temp;
  temp = text;
  std::size_t poss = temp.find("/");
  std::size_t poss1 = temp.find("/", (int)poss + 1);
  std::string sum = temp.substr(0, poss);
  std::string term = temp.substr((int)poss + 1, (int)poss1 - (int)poss - 1);
  std::string rate = temp.substr((int)poss1 + 1);
  credit.sum = sum;
  credit.term = term;
  credit.rate = rate;
  credit.is_data_entred = true;
  reset_after_answer(text);
  return credit;
}

credit_report Model::report_init(credit_data credit) {
  credit_report report;
  report.term = atoi(credit.term.c_str());
  report.month = get_month();
  report.sum = atof(credit.sum.c_str());
  report.rate = atof(credit.rate.c_str());
  return report;
}

credit_report Model::differ_credit_calc(credit_report report) {
  double total_overpayment = 0.0;
  double credit_sum = report.sum;
  double part_of_sum = credit_sum / report.term;
  double current_sum = credit_sum;
  int current_month = get_month();
  for (int i = 0; i < report.term; i++) {
    snprintf(report.loan_balance[i], sizeof(char)*300, "%.2f", current_sum);
    double month_pay_rate = current_sum *(report.rate/100.0) * (day_in_month(current_month) / 365.0);
    current_sum -= part_of_sum;
    total_overpayment += (round(month_pay_rate*100.0))/100;
    snprintf(report.month_pay[i], sizeof(char)*300, "%.2f", month_pay_rate);
    double total_month_pay = (round(month_pay_rate + (credit_sum / report.term)));
    snprintf(report.total_month_pay[i], sizeof(char)*300, "%.2f", total_month_pay);
  }
  snprintf(report.total_credit, sizeof(char)*300, "%.2f", total_overpayment + credit_sum);
  snprintf(report.total_overpayment, sizeof(char)*300, "%.2f", total_overpayment);
  return report;
}

credit_report Model::annuity_credit_calc(credit_report report) {
  double month_rate = report.rate / 12 / 100.0;
  double month = report.term;
  double ann_cf = ((month_rate * pow(1.0+month_rate, month)) / (pow(1.0+month_rate, month)-1));
  double month_pay = report.sum * ann_cf;
  double au_total_credit = month_pay * report.term;
  snprintf(report.au_month_pay, sizeof(char)*300, "%.2f", month_pay);
  snprintf(report.au_total_credit, sizeof(char)*300, "%.2f", au_total_credit);
  snprintf(report.au_total_overpayment, sizeof(char)*300, "%.2f", au_total_credit - report.sum);
  return report;
}

int Model::get_month() {
  struct tm time_info;
    time_t tm;
    time(&tm);
    localtime_s(&time_info, &tm);
    return time_info.tm_mon;
}

int Model::day_in_month(int x) {
  int result = (int)(28 + (int)(x + floor(x/8)) % 2 + 2 % x + 2 * floor(1/x));
  return result;
}

void Model::smart_calc(expression* expr, std::string& input_string) {
//  std::cout << "line 580: func smart_calc, input_string = " << input_string << std::endl;///
  create_expression(expr, input_string);
  parsing(expr);
  polish_converter(expr);
  opz_calculator(expr);
}

void Model::opz_calculator(expression* expr) {
//   std::cout << "Line 594: func opz_calculator, expr = " << expr->input_string << std::endl;  ///
  std::string pln_str = expr->input_string;
  std::size_t len = pln_str.length();
  expr->size_d_list = 0;
  for (int i = 0; i < (int)len; i++) {
    if (pln_str[i] == 'D') {
      put_num_in_temp(expr, 'D');
    } else if (pln_str[i] == 'Z') {
      put_num_in_temp(expr, 'Z');
    } else {
      calculate(expr, pln_str[i]);
    }
  }
}

void Model::put_num_in_temp(expression* expr, char ch) {

  if (ch == 'D') {
    expr->temp_stack[expr->temp_index] = expr->list_of_digitals[expr->size_d_list];

//    std::cout << "line 614: func put_num_in_temp, expr->size_d_list = " << expr->size_d_list <<
//        " ch = " << ch << " expr->temp_index = " << expr->temp_index << std::endl
//        << " expr->list_of_digitals[expr->size_d_list] = " << expr->list_of_digitals[expr->size_d_list]
////        << std::endl;///

    expr->size_d_list += 1;
  } else {
    expr->temp_stack[expr->temp_index] = 0.0;
  }
  expr->temp_index += 1;
}

void Model::calculate(expression* expr, char operator_) {
////    std::cout << "Line 627: func calculate, expr = " << expr->input_string << " operator = " << operator_ << std::endl;///
//    ///
  double y = expr->temp_stack[expr->temp_index-1];
////  std::cout << "line 630:func calculate, y = " << y << std::endl;///
  expr->temp_stack[expr->temp_index-1] = 0.0;
  expr->temp_index -= 1;
  double r_digit;
  std::string s("LOINQCSTG");
  if (is_char_equal(operator_, s)) {
////    std::cout << "Line 636: func calculate" << std::endl;  ///
    r_digit = function_calculate(y, operator_);
  } else if (expr->temp_index == 0 && operator_ == '-') {
////    std::cout << "Line 639: func calculate" << std::endl;  ///
    r_digit = digits_calculate(0, y, operator_);
  } else {
    double x = expr->temp_stack[expr->temp_index-1];
    expr->temp_stack[expr->temp_index-1] = 0.0;
    expr->temp_index -= 1;
    r_digit = digits_calculate(x, y, operator_);
  }
////  std::cout << "Line 647: func calculate r_digit =  " << r_digit << std::endl;  ///
  add_result_double_to_temp(expr, r_digit);
}

double Model::function_calculate(double num, char fn) {
////    std::cout << "line 652: func function_calculate, num = " << num << " fn = " << fn << std::endl;///
  double r_digit = 0;
  if (fn == 'O') {
    r_digit = acos(num);
  } else if (fn == 'I') {
    r_digit = asin(num);
  } else if (fn == 'N') {
    r_digit = atan(num);
  } else if (fn == 'C') {
    r_digit = cos(num);
  } else if (fn == 'S') {
    r_digit = sin(num);
  } else if (fn == 'T') {
    r_digit = tan(num);
  } else if (fn == 'G') {
    r_digit = log10(num);
  } else if (fn == 'L') {
    r_digit = log(num);
  } else if (fn == 'Q') {
    if (num < 0) {
      r_digit = NAN;
    } else {
      r_digit = sqrt(num);
    }
  }
  return r_digit;
}

double Model::digits_calculate(double x, double y, char operator_) {
  double r_digit;
  r_digit = double_calc(x, y, operator_);
return r_digit;
}

double Model::double_calc(double x, double y, char operator_) {
double result = 0;
  if (operator_ == '-') {
    result = x - y;
  } else if (operator_ == '+') {
    result = x + y;
  } else if (operator_ == '*') {
    result = x * y;
  } else if (operator_ == '/') {
    result = x / y;
  } else if (operator_ == '^') {
    result = pow(x, y);
  } else if (operator_ == '#') {
    result = fmod(x, y);
  }
return result;
}

void Model::add_result_double_to_temp(expression* expr, double digit) {
  expr->temp_stack[expr->temp_index] = digit;
  expr->temp_index += 1;
}

void Model::input_string_cleaner(expression* expr) {
  space_remover(expr);
  sign_cleaner(expr);
  remove_plus_at_start_in_string(expr);
}

void Model::sign_cleaner(expression* expr) {
  sign current_sign, prv_sign = sign::NONE;
  std::size_t len = expr->input_string.length();
  std::string temp;
  remove_plus_at_start_in_string(expr);
  char ch;
  for (int i = 0, t = 0; i < (int)len; i++) {
    ch = expr->input_string[i];
    current_sign = is_sign(ch);
    if (current_sign != sign::NONE) {
      if (prv_sign == sign::NONE) {
        prv_sign = current_sign;
      } else {
        prv_sign = set_sign(current_sign, prv_sign);
        ch = get_sign_char(prv_sign);
        t--;
      }
    } else {
      prv_sign = sign::NONE;
    }
    temp.replace(t, 1, 1, ch);
    t++;
  }
  create_expression(expr, temp);
}

void Model::remove_plus_at_start_in_string(expression* expr) {
  std::size_t len = expr->input_string.length();
  std::string temp;
  bool skip = true;
  int t = 0;
  for (int i = 0; i < (int)len; i++) {
    char ch = expr->input_string[i];
    if (ch == '+' && skip) {
    } else {
      skip = false;
      temp.replace(t, 1, 1, ch);
      t++;
    }
  }
  temp.resize(t);
  create_expression(expr, temp);
}

sign Model::is_sign(char ch) {
  sign r_sign = sign::NONE;
  if (ch == '-') {
    r_sign = sign::MINUS;
  } else if (ch == '+') {
    r_sign = sign::PLUS;
  }
  return r_sign;
}

sign Model::set_sign(sign current_sign, sign prv_sign) {
  if (current_sign == prv_sign && current_sign == sign::MINUS) {
    prv_sign = sign::PLUS;
  } else if (current_sign == sign::MINUS || prv_sign == sign::MINUS) {
    prv_sign = sign::MINUS;
  }
  return prv_sign;
}

char Model::get_sign_char(sign signf) {
  return signf == sign::PLUS ? '+':'-';
}

void Model::space_remover(expression* expr) {
  std::size_t len = expr->input_string.length();
  if ((int)len > 0) {
    std::string temp;
    copy_str_without_spaces(temp, expr->input_string, " ");
    expr->input_string = temp;
  }
}

void Model::copy_str_without_spaces(std::string& dst, std::string& src, const char *symbls) {
  std::string s(symbls);
  std::size_t len = src.length();
  int i = 0;
  for (int d = 0; i < (int)len; i++) {
    if (!is_char_equal(src[i], s)) {
      dst.replace(d, 1, 1, src[i]);
      d++;
    }
  }
  src.resize(i);
}

void Model::init_expression(expression* src) {
  src->size_d_list = 0;
  src->size_f_list = 0;
  src->f_index = 0;
  src->temp_index = 0;
}

void Model::create_expression(expression* expr_r, std::string& src) {
  init_expression(expr_r);
  if (!src.empty()) {
    expr_r->input_string = src;
  } else {
    expr_r->input_string = "";
  }
  put_zero_to_digit_list_all_elem(expr_r->temp_stack);
  put_zero_to_digit_list_all_elem(expr_r->list_of_digitals);
}

void Model::put_zero_to_digit_list_all_elem(double *array) {
  for (int i = 0; i < 256; i++) {
      array[i] = 0.0;
  }
}

void Model::zero_remover(std::string& src) {
  std::size_t len = src.length();
  bool next = true;
  for (int i = (int)len - 1; next; i--) {
      if (src[i] == '0') {
          src.resize(i);
      } else if (src[i] == '.') {
          src.resize(i);
          next = false;
      } else {
          next = false;
      }
  }
}

void Model::parsing(expression* expr) {
  input_string_cleaner(expr);
  get_functions(expr);
  get_numbers(expr);
  set_unarn_sign(expr);
}

void Model::set_unarn_sign(expression* expr) {
  std::string temp, s("(*^/");
  std::string ex = expr->input_string;
  int t_indx = 0;
  std::size_t ln = ex.length();
  for (int i = 0; i < (int)ln; i++) {
    if (ex[i] == '-') {
      if ((is_char_equal(ex[i-1], s) && ex[i+1] == 'D') || i == 0) {
        if (i == 0) {
          temp.append("Z-");
          t_indx+=2;
        } else {
          temp.append("(Z-D)");
          t_indx+=5;
          i++;
        }
      } else {
          temp.replace(t_indx, 1, 1, ex[i]);
          t_indx++;
      }
    } else {
        temp.replace(t_indx, 1, 1, ex[i]);
        t_indx++;
    }
  }
  temp.resize(t_indx);
  expr->input_string = temp;
}

void Model::get_functions(expression* expr) {
  size_t len = expr->input_string.length();
  for (int i = 0; i < (int)len; i++) {
    char ch = expr->input_string[i];
    std::string s("1234567890.-+*/^()F#");
    bool isFind = is_char_equal(ch, s);
    if (!isFind) {
      get_funct_type(expr, i);
    }
  }
  remove_extra_F(expr);
}

char Model::set_funct(int index) {
  char fun;
  if (index == 0) {         // ln
      fun = 'L';
  } else if (index == 1) {  // acos
      fun = 'O';
  } else if (index == 2) {  // asin
      fun = 'I';
  } else if (index == 3) {  // atan
      fun = 'N';
  } else if (index == 4) {  // sqrt
      fun = 'Q';
  } else if (index == 5) {  // cos
      fun = 'C';
  } else if (index == 6) {  // sin
      fun = 'S';
  } else if (index == 7) {  // tan
      fun = 'T';
  } else if (index == 8) {  // log
      fun = 'G';
  }
  return fun;
}

void Model::get_funct_type(expression* expr, int index) {
  std::string temp;
  copy_array_part(temp, expr->input_string, index);
  bool is_find = false;
  const char *functions[] = {
      "ln",
      "acos", "asin", "atan", "sqrt",
      "cos", "sin", "tan", "log", "mod"
  };
  int f_len = 2;
  for (int i = 0; i < 10 && !is_find; i++) {
    if (temp.find(functions[i]) != std::string::npos) {
      is_find = true;
      if (i > 0) {
        f_len = (i <= 4) ? 4 : 3;
      }
      if (i == 9) {
        expr->input_string.replace(index, f_len, f_len, '!');
        expr->input_string.replace(index, 1, 1, '#');
      } else {
        expr->input_string.replace(index, f_len, f_len, '!');
        expr->input_string.replace(index, 1, 1, set_funct(i));
      }
    }
  }
}

void Model::remove_extra_F(expression* expr) {
  std::string temp = expr->input_string;
  std::size_t len = expr->input_string.length();
  bool skip_F = false;
  int k = 0;
  for (int i = 0; i < (int)len; i++) {
    char ch = expr->input_string[i];
    if ((ch == 'F' && skip_F) || ch == '!') {
    } else {
      skip_F = (ch == 'F' && !skip_F) ? true : false;
      expr->input_string.replace(k, 1, 1, temp[i]);
      k++;
    }
  }
  expr->input_string.resize(k);
}

void Model::copy_array_part(std::string& dst, std::string& src, int start_index) {
  std::size_t len = src.length();
  int token_len = (int)len - start_index < 4 ? (int)len : 4;
  for (int i = 0; i < token_len; i++) {
    dst.replace(i, 1, 1, src[start_index + i]);
  }
}

void Model::get_numbers(expression* expr) {
  std::string temp = expr->input_string;
////  std::cout << "line 970: expr->input_string = " << expr->input_string << std::endl;///
  std::size_t ln = expr->input_string.length();
  char* vv = NULL;
  const char* tok = "";
  const char* separators = "#LOINQCSTG+-*/^()";
  for (int i = 0; i < (int)ln && tok; i++) {
    if (i == 0) {
      tok = strtok_s((char*)temp.c_str(), separators, &vv);
    } else {
      tok = strtok_s(NULL, separators, &vv);
    }
    if (tok) {
      str_num_to_digital(expr, tok);
    }
  }
  std::string s("0123456789.");
  remove_all_numbers_from_str(expr, s);
}

void Model::remove_all_numbers_from_str(expression* expr, std::string& extra) {
  std::string temp = expr->input_string;
  std::size_t len = expr->input_string.length();
  bool skip = false;
  int k = 0;
  for (int i = 0; i < len; i++) {
    char ch = expr->input_string[i];
    bool is_number = is_char_equal(ch, extra);
    if (is_number && skip) {
    } else {
      if (is_number && !skip) {
        skip = true;
        expr->input_string.replace(k, 1, 1, 'D');
        k++;
      } else {
        skip = false;
      }
      if (!is_number) {
        expr->input_string.replace(k, 1, 1, temp[i]);
        k++;
      }
    }
  }
  expr->input_string.resize(k);
}

bool Model::validator(std::string& text) {
////  std::cout << "line 1010: func - validator, text = " << text << std::endl;///
  std::string temp(300, '\0');
  std::string func_temp(300, '\0');
  std::string name_temp(300, '\0');
  func_temp = text;
  name_temp = text;
  set_x_to_temp_number_for_check(func_temp);
  check_func_name(func_temp);
  if (func_temp.find("E") != std::string::npos) calc_exponential(func_temp);
  set_x_to_temp_number_for_check(temp);
  change_funct_to_F(temp, text);
  bool is_correct = check_breaker(text);
////  std::cout << "line 1022: is_correct = " << is_correct << std::endl;///
  if (is_correct) {
      is_correct = is_first_last_ch_correct(temp);
  }
////  std::cout << "line 1026: is_correct = " << is_correct << std::endl;///
  if (is_correct) {
      is_correct = check_str_for_reg(temp, func_temp, text);
  }
////  std::cout << "line 1035: is_correct = " << is_correct << std::endl;///
  return is_correct;
}

void Model::calc_exponential(std::string& str) {
  std::string temp(in_text.outpt_text), dig;
  int degree_i = 0;
  long double num_i = 0.0, result = 0.0;
  std::size_t pos = temp.find("E"), pos_left = pos - 1, pos_right = pos + 2;
  if (pos != std::string::npos) dig.append(temp, pos, 2);
  if (dig == "E+" || dig == "E-") {
    std::string right_("0123456789"), left_("0123456789."), sign(temp, (int)pos + 1, 1);
    while (is_char_equal(temp[pos_left], left_)) {
      if ((int)pos_left != 0) {
        --pos_left;
      } else {
        break;
      }
    }
    if ((int)pos_left != 0) ++pos_left;
    std::string num(temp, pos_left, (int)pos - (int)pos_left);  //  число
    while (is_char_equal(temp[pos_right], right_)) {
      if (pos_right != temp.length()) {
        ++pos_right;
       } else {
        break;
       }
    }
    if (pos_right != temp.length()) --pos_right;
    std::string degree(temp, (int)pos + 2, (int)pos_right - ((int)pos + 1));  //  степень
    if (chek_exp_digits(num, "0123456789.") && chek_exp_digits(degree, "0123456789")) {
      if (pos != std::string::npos) str.erase(str.find("E"), 1);
      num_i = std::stold(num);
      degree_i = std::stoi(degree);   //  степень
      if (sign == "+") {
        result = num_i * pow(10.0, degree_i);
      } else if (sign == "-") {
        result = num_i / pow(10.0, degree_i);
      }
      std::string res_left(temp, 0, (int)pos_left), res_right;
      if ((int)pos_right < (int)temp.length() - 1) {
        std::string t_m(temp, (int)pos_right + 1);
        res_right = t_m;
      }
      std::string out(res_left), res_str(std::to_string(result));
      zero_remover(res_str);
      out.append(res_str);
      out.append(res_right);
      in_text.outpt_text = out;
      in_text.text = out;
    }
  }
}

bool Model::chek_exp_digits(std::string& str, const std::string& template_) {
  size_t len = str.length();
  bool res = true;
  for (int i = 0; i < int(len); i++) {
    if (template_.find(str[i]) == std::string::npos) res = false;
  }
  return (int)len == 0 ? false : res;
}

void Model::check_func_name(std::string& text) {
  std::string s("1234567890.-+*/^()");
  std::vector<std::string> functions {
      "ln",
      "acos", "asin", "atan", "sqrt",
      "cos", "sin", "tan", "log", "mod"
  };

  std::size_t len = text.length();
  for (int i = 0; i < (int)len; i++) {
      if (is_char_equal(text[i], s)) {
          text.replace(i, 1, 1, ' ');
      }
  }

  int f_len = 2;
  for (int k = 0; k < 10; k++) {
    std::size_t g = text.find(functions[k]);
      if (k > 0) {
          f_len = (k <= 4) ? 4 : 3;
      }
      while (g != std::string::npos) {
        text.replace(g, (std::size_t)f_len, " ");
          g = text.find(functions[k]);
      }
  }
}

bool Model::check_str_for_reg(std::string& temp, std::string& func_temp, std::string& text) {
  bool is_correct;
//  std::cout << "line 1050: func - check_str_for_reg, text = " << text << std::endl;////////////
//  std::cout << "line 1051: is_correct = " << is_correct << std::endl;/////////////
//  regex_t     regex;
//  regmatch_t  pmatch[1];
  std::string template_ =
          "(mFF){2,}.*|"
          "\\((mFF)+[0-9]+.*|"
          "[^0-9]+(mFF).*|"
          "[0-9]+(mFF)[+-]*[^0-9]+|"
          "\\([\\*\\/^]+[0-9]+.*|"
          "\\([*/^+-.]+\\).*|"
          "\\([+-]*[0-9]+[-+*/^]+\\).*|"
          ".*[0-9]+[\\/*^m]{2,}.*|"
          "[+-]+[*/^m]+|"
          "0{2,}\\..*|"
          "\\.{2,}|"
          "[^0-9]+\\.+[^0-9]+|"
          "[0-9]+\\.+[^0-9]+|"
          "[^0-9]+\\.+[0-9]+|"
          "[0-9]+\\.[0-9]+\\.[0-9]+|"
          "[0-9]{17,}|"
          "[0-9]+\\(|"
          "\\)[0-9]+|"
          ".*(\\(\\)).*";
//  regcomp(&regex, template_, REG_EXTENDED);
//  is_correct = regexec(&regex, temp.c_str(), ARRAY_SIZE(pmatch), pmatch, 0);
//  regfree(&regex);
    is_correct = std::regex_match(temp, std::regex(template_));
//    std::cout << "line 1078: is_correct = " << is_correct << std::endl;/////////////
  if (!is_correct) {
    std::string temp = "[a-zA-Z]+";
//      regcomp(&regex, "[a-zA-Z]+", REG_EXTENDED);
//      is_correct = regexec(&regex, func_temp.c_str(), ARRAY_SIZE(pmatch), pmatch, 0);
//      regfree(&regex);
        is_correct = std::regex_match(func_temp, std::regex(temp));
//        std::cout << "line 1085: is_correct = " << is_correct << std::endl;/////////////
  }
  if (!is_correct) {
      std::string func_template =
          "[b-z](sin){1}|[b-z](cos){1}|[b-z](tan){1}|"
          "[a-z](log){1}|[a-z](ln){1}|[a-z](sqrt){1}|"
          "[a-z](asin){1}|[a-z](acos){1}|[a-z](atan){1}|"
          "[0-9]+x|x[0-9]+";
//      regcomp(&regex, func_template, REG_EXTENDED);
//      is_correct = regexec(&regex, text.c_str(), ARRAY_SIZE(pmatch), pmatch, 0);
//      regfree(&regex);
        is_correct = std::regex_match(text, std::regex(func_template));
//        std::cout << "line 1097: is_correct = " << is_correct << std::endl;/////////////
  }
  return is_correct == 0 ? 1 : 0;
}

bool Model::is_first_last_ch_correct(std::string& text) {
  std::string s(".*/^m"), s1("(+-*/Fm");
    bool is_correct = true;
    if (is_char_equal(text[0], s)) {
        is_correct = false;
    }
    if (is_char_equal(text[(int)(text.length()) - 1], s1)) {
        is_correct = false;
    }
    return is_correct;
}

int Model::check_breaker(std::string& text) {
  bool is_correct = true;
  int open_br = 0;
  std::size_t len = text.length();
  for (int i = 0; i < (int)len && is_correct; i++) {
    char ch = text[i];
    if (ch == '(') {
        open_br++;
    } else if (ch == ')') {
        open_br--;
        if (open_br < 0) {
            is_correct = false;
        }
    }
  }
  if (open_br > 0) {
      is_correct = false;
  }
  return is_correct;
}

void Model::set_x_to_temp_number_for_check(std::string& text) {
  std::size_t len = text.length();
  for (int i = 0; i < (int)len; i++) {
    if (text[i] == 'x') {
      text.replace(i, 1, 1, 1);
    }
  }
}

void Model::change_funct_to_F(std::string& dst, std::string& src) {
  std::string s("E1234567890.-+*/^()mx");
  std::size_t len = src.length();
  dst.clear();
  int d = 0;
  for (int i = 0; i < (int)len; i++) {
      if (!is_char_equal(src[i], s)) {
          dst.replace(d, 1, 1, 'F');
          d++;
      } else {
          dst.replace(d, 1, 1, src[i]);
          d++;
      }
  }
  dst.resize(d);
}

Model::draw_scale Model::draw_sc_init() {
  Model::draw_scale draw_sc;
  draw_sc.x_min = in_text.x_min;
  draw_sc.x_max = in_text.x_max;
  draw_sc.y_min = in_text.y_min;
  draw_sc.y_max = in_text.y_max;
  draw_sc.total_x = fabs(draw_sc.x_min) + fabs(draw_sc.x_max);
  draw_sc.total_y = fabs(draw_sc.y_min) + fabs(draw_sc.y_max);;
  draw_sc.step_x = draw_sc.total_x / 2000;
  draw_sc.step_y = 2000.0 / round(fabs(draw_sc.y_max - draw_sc.y_min));
  draw_sc.x_zero = 2000 - (int)((2000/draw_sc.total_y) * (0 - draw_sc.y_min));
  draw_sc.y_zero = (int)((2000/draw_sc.total_x) * (0-draw_sc.x_min));
  std::cout << "Init line 1254: x_min = " << draw_sc.x_min << " x_max = " << draw_sc.x_max
  << " y_min = " << draw_sc.y_min << " y_max = " << draw_sc.y_max << std::endl;
  return draw_sc;
}

credit_data Model::credit_init() {
  credit_data credit;
  credit.is_data_entred = false;
  return credit;
}


}  // namespace s21
