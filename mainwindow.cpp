#include "mainwindow.h"
#include "algo.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <algorithm>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    deque_model_.iterator = deque_model_.items.begin();
    ui->lbl_count->setText("0");
    ApplyModel();
    ApplyIterator();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    bool is_empty = deque_model_.items.empty();
    ui->btn_pop_back->setEnabled(!is_empty);
    ui->btn_pop_front->setEnabled(!is_empty);
    ui->btn_erase->setEnabled(!is_empty);

    auto iterator_temp = deque_model_.iterator;

    ui->list_widget->clear();
    for (std::size_t i = 0; i < deque_model_.items.size(); i++) {
        ui->list_widget->addItem(QString::fromStdString(std::to_string(i) + ": " + deque_model_.items[i]));
    }
    ui->list_widget->addItem(QString("end"));

    deque_model_.iterator = iterator_temp;

    ui->txt_size->setText(QString::number(deque_model_.items.size()));
}

void MainWindow::ApplyIterator() {
    int num = std::distance(deque_model_.iterator, deque_model_.items.begin());
    ui->list_widget->setCurrentRow(std::abs(num));

    ui->btn_inc_iterator->setEnabled(deque_model_.iterator != deque_model_.items.end());
    ui->btn_erase->setEnabled(deque_model_.iterator != deque_model_.items.end());
    ui->btn_dec_iterator->setEnabled(deque_model_.iterator != deque_model_.items.begin());
    ui->btn_edit->setEnabled(deque_model_.iterator != deque_model_.items.end());

    ui->txt_elem_content->setText(deque_model_.iterator == deque_model_.items.end() ? "" : QString::fromStdString(*deque_model_.iterator));
}

void MainWindow::on_btn_clear_clicked() {
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_push_front_clicked() {
    std::string temp = ui->txt_elem_content->text().toStdString();
    deque_model_.items.push_front(temp);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_push_back_clicked() {
    std::string temp = ui->txt_elem_content->text().toStdString();
    deque_model_.items.push_back(temp);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_pop_front_clicked() {
    if (!deque_model_.items.empty()) {
        deque_model_.items.pop_front();
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
        ApplyIterator();
    }
}

void MainWindow::on_btn_pop_back_clicked() {
    if (!deque_model_.items.empty()) {
        deque_model_.items.pop_back();
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
        ApplyIterator();
    }
}

void MainWindow::on_btn_insert_clicked() {
    std::string temp = ui->txt_elem_content->text().toStdString();
    deque_model_.items.insert(deque_model_.iterator, temp);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_erase_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        deque_model_.items.erase(deque_model_.iterator);
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
        ApplyIterator();
    }
}

void MainWindow::on_btn_begin_clicked() {
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_end_clicked() {
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}

void MainWindow::on_btn_dec_iterator_clicked() {
    if (deque_model_.iterator > deque_model_.items.begin()) {
        --deque_model_.iterator;
    }
    ApplyIterator();
}

void MainWindow::on_btn_inc_iterator_clicked() {
    if (deque_model_.iterator < deque_model_.items.end()) {
        ++deque_model_.iterator;
    }
    ApplyIterator();
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow < 0) {
        return; // Убираем проверку на размер
    }
    if (currentRow < static_cast<int>(deque_model_.items.size())) {
        deque_model_.iterator = deque_model_.items.begin() + currentRow;
    } else {
        deque_model_.iterator = deque_model_.items.end();
    }
    ApplyIterator();
}

void MainWindow::on_btn_tea_clicked() {
    deque_model_.items = {
        "Чай Лунцзин",
        "Эрл Грей",
        "Сенча",
        "Пуэр",
        "Дарджилинг",
        "Ассам",
        "Матча",
        "Ганпаудер",
        "Оолонг",
        "Лапсанг Сушонг"
    };
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_cakes_clicked() {
    deque_model_.items = {
        "Красный бархат",
        "Наполеон",
        "Медовик",
        "Тирамису",
        "Прага",
        "Чизкейк",
        "Захер",
        "Эстерхази",
        "Морковный торт",
        "Чёрный лес",
    };
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_merge_sort_clicked() {
    if (!deque_model_.items.empty()) {
        std::sort(deque_model_.items.begin(), deque_model_.items.end(), std::less<std::string>());
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
        ApplyIterator();
    }
}

void MainWindow::on_btn_upper_bound_clicked() {
    if (deque_model_.items.empty()) {
        return;
    }

    std::string value = ui->txt_elem_content->text().toStdString();
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto it = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), value);
        deque_model_.iterator = it;
        ApplyIterator();
    }
}

void MainWindow::on_btn_lower_bound_clicked() {
    if (deque_model_.items.empty()) {
        return;
    }
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        std::string value = ui->txt_elem_content->text().toStdString();
        auto it = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), value);
        deque_model_.iterator = it;
        ApplyIterator();
    }
}

void MainWindow::on_btn_edit_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        std::string temp = ui->txt_elem_content->text().toStdString();
        int index = std::abs(std::distance(deque_model_.iterator, deque_model_.items.begin()));
        deque_model_.items[index] = temp;
        ApplyModel();
        ApplyIterator();
    }
}

void MainWindow::on_btn_find_clicked() {
    deque_model_.iterator = std::find(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
    ApplyIterator();
}

void MainWindow::on_btn_count_clicked() {
    int num = std::count(deque_model_.items.begin(), deque_model_.items.end(), ui->le_count->text().toStdString());
    ui->lbl_count->setText(QString::number(num));
}

void MainWindow::on_btn_min_element_clicked() {
    if (!deque_model_.items.empty()) {
        deque_model_.iterator = std::min_element(deque_model_.items.begin(), deque_model_.items.end());
        ApplyIterator();
    }
}

void MainWindow::on_btn_max_element_clicked() {
    if (!deque_model_.items.empty()) {
        deque_model_.iterator = std::max_element(deque_model_.items.begin(), deque_model_.items.end());
        ApplyIterator();
    }
}

void MainWindow::on_btn_merge_sOrT_clicked() {
    std::sort(deque_model_.items.begin(), deque_model_.items.end(), [](const std::string& s1, const std::string& s2) {
        return QString::compare(QString::fromStdString(s1), QString::fromStdString(s2), Qt::CaseInsensitive) < 0;
    });
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_unique_clicked() {
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto pos = std::unique(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.items.erase(pos, deque_model_.items.end());
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
        ApplyIterator();
    }
}

void MainWindow::on_btn_reverse_clicked() {
    auto current_it = deque_model_.iterator;
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    int distance = std::distance(deque_model_.items.begin(), current_it);
    deque_model_.iterator = deque_model_.items.begin();
    std::advance(deque_model_.iterator, distance);

    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_shuffle_clicked() {
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), gen);
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_resize_clicked() {
    int size = ui->txt_size->text().toInt();
    deque_model_.items.resize(size);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::SetRandomGen(const std::mt19937& random_gen) {
    gen = random_gen;
}