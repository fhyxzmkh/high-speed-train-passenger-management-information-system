#pragma once

#include "train.h"

struct BstNode {
    std::size_t price;
    std::shared_ptr<PassengerNode> passengers;
    std::shared_ptr<BstNode> left;
    std::shared_ptr<BstNode> right;

    BstNode(std::size_t p, std::shared_ptr<PassengerNode> ps)
        : price(p), passengers(ps), left(nullptr), right(nullptr) {}
};

struct BstTree {
    std::shared_ptr<BstNode> root;

    BstTree() : root(nullptr) {}

    void insert(std::size_t price, std::shared_ptr<PassengerNode> passengerNode) {
        root = insertRec(root, price, passengerNode);
    }

    void inorder() {
        inorderRec(root);
    }

    std::size_t getPassengerGetInCountByStations(std::string station_) {
        std::size_t cnt{};
        getPassengerGetInCountByStationsRec(root, station_, cnt);
        return cnt;
    }

    std::size_t getPassengerGetOutCountByStations(std::string station_) {
        std::size_t cnt{};
        getPassengerGetOutCountByStationsRec(root, station_, cnt);
        return cnt;
    }

    bool searchPassengerById(std::string id_) {
        return searchPassengerByIdRec(root, id_);
    }

    std::vector<Passenger> getPassengerInfo() {
        std::vector<Passenger> passengers_;
        getPassengerInfoRec(root, passengers_);
        return passengers_;
    }

    void updatePassengInfo(Passenger np) {
        updatePassengInfoRec(root, np);
    }

    void deletePassengInfo(std::string id_) {
        root = deletePassengInfoRec(root, id_);
    }

private:
    std::shared_ptr<BstNode> insertRec(std::shared_ptr<BstNode> node, std::size_t price, std::shared_ptr<PassengerNode> passengerNode) {
        if (node == nullptr) {
            return std::make_shared<BstNode>(price, passengerNode);
        }

        if (price < node->price) {
            node->left = insertRec(node->left, price, passengerNode);
        }
        else if (price > node->price) {
            node->right = insertRec(node->right, price, passengerNode);
        }
        else {
            // 如果价格相同，将乘客添加到当前节点的链表中
            passengerNode->next = node->passengers;
            node->passengers = passengerNode;
        }

        return node;
    }

    void inorderRec(std::shared_ptr<BstNode> node) {
        if (node != nullptr) {
            inorderRec(node->left);
            if (!node->passengers) return;

            std::cout << "\n票价：" << node->price << "，同票价乘客：" << std::endl;
            auto current = node->passengers;
            while (current != nullptr) {
                current->value.printInfo();
                current = current->next;
            }
            std::cout << std::endl;
            inorderRec(node->right);
        }
    }

    void getPassengerGetInCountByStationsRec(std::shared_ptr<BstNode> node, std::string station_, std::size_t& cnt) {
        if (node != nullptr) {
            getPassengerGetInCountByStationsRec(node->left, station_, cnt);
            auto current = node->passengers;
            while (current != nullptr) {
                if (current->value.start_station == station_) cnt += 1;
                current = current->next;
            }
            getPassengerGetInCountByStationsRec(node->right, station_, cnt);
        }
    }

    void getPassengerGetOutCountByStationsRec(std::shared_ptr<BstNode> node, std::string station_, std::size_t& cnt) {
        if (node != nullptr) {
            getPassengerGetOutCountByStationsRec(node->left, station_, cnt);
            auto current = node->passengers;
            while (current != nullptr) {
                if (current->value.end_station == station_) cnt += 1;
                current = current->next;
            }
            getPassengerGetOutCountByStationsRec(node->right, station_, cnt);
        }
    }

    bool searchPassengerByIdRec(std::shared_ptr<BstNode> node, std::string id_) {
        if (node == nullptr) {
            return false;
        }

        // 先在左子树中查找
        if (searchPassengerByIdRec(node->left, id_)) {
            return true;
        }

        // 在当前节点的乘客链表中查找
        auto current = node->passengers;
        while (current != nullptr) {
            if (current->value.id == id_) {
                return true;
            }
            current = current->next;
        }

        // 最后在右子树中查找
        return searchPassengerByIdRec(node->right, id_);
    }

    void getPassengerInfoRec(std::shared_ptr<BstNode> node, std::vector<Passenger>& passengers_) {
        if (node != nullptr) {
            getPassengerInfoRec(node->left, passengers_);
            auto current = node->passengers;
            while (current != nullptr) {
                passengers_.push_back(current->value);
                current = current->next;
            }
            getPassengerInfoRec(node->right, passengers_);
        }
    }

    void updatePassengInfoRec(std::shared_ptr<BstNode> node, Passenger np) {
        if (node != nullptr) {
            updatePassengInfoRec(node->left, np);
            auto current = node->passengers;
            while (current != nullptr) {
                if (current->value.id == np.id) {
                    current->value = np;
                    return;
                }
                current = current->next;
            }
            updatePassengInfoRec(node->right, np);
        }
    }

    std::shared_ptr<BstNode> deletePassengInfoRec(std::shared_ptr<BstNode> node, std::string id_) {
        if (node == nullptr) {
            return nullptr;
        }

        // 先递归处理左右子树
        node->left = deletePassengInfoRec(node->left, id_);
        node->right = deletePassengInfoRec(node->right, id_);

        // 处理当前节点的乘客链表
        auto current = node->passengers;
        std::shared_ptr<PassengerNode> prev = nullptr;

        while (current != nullptr) {
            if (current->value.id == id_) {
                if (prev == nullptr) {
                    // 如果删除的是头节点
                    node->passengers = current->next;
                }
                else {
                    // 如果删除的是中间或尾节点
                    prev->next = current->next;
                }
                break;
            }
            prev = current;
            current = current->next;
        }

        return node;
    }

};