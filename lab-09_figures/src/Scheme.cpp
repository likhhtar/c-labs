#include "Scheme.hpp"

Scheme::Scheme(int capacity){
    figures_ = new Figure * [capacity];
    size_ = 0;
    capacity_ = capacity;
}
Scheme::~Scheme(){
    for (int i = 0; i < size_; i++){
        delete figures_[i];
    }
    delete[] figures_;
}

void Scheme::push_back_figure(Figure* fg){
    if(size_ >= capacity_) return;
    figures_[size_++] = fg;
}
void Scheme::remove_figure(int id) {
    int i = find_by_id(id);
    if (i == -1) return;

    delete figures_[i];
    for (int j = i; j < size_ - 1; j++){
        figures_[j] = figures_[j + 1];
    }
    size_--;
}

void Scheme::print_all_figures(){
    for (int i = 0; i < size_; i++){
        figures_[i]->print();
    }
}
void Scheme::zoom_figure(int id, int factor){
    int i = find_by_id(id);
    if (i == -1 || factor < 0) return;
    figures_[i]->zoom(factor);
}
Figure* Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < size_; i++){
        if (figures_[i]->is_inside(x, y)){
            return figures_[i];
        }
    }
    return nullptr;
}
void Scheme::move(int id, int new_x, int new_y){
    int i = find_by_id(id);
    if (i == -1) return;
    figures_[i]->move(new_x, new_y);
}

int Scheme::find_by_id(int id){
    for (int i = 0; i < size_; i++) {
        if (figures_[i]->get_id() == id) {
            return i;
        }
    }
    return -1;
}
