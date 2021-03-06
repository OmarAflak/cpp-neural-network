#include <iostream>

#include "../network/network.h"
#include "../layers/fc_layer.h"
#include "../layers/activation_layer.h"
#include "../losses/losses.h"
#include "../activations/activations.h"

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for(int i=0 ; i<v.size() ; i++) {
        os << v[i];
        if(i+1!=v.size()) {
            os << ",";
        }
    }
    os << "]";
    return os;
}

int main(int argc, char const *argv[]) {
    util::initRand();
    std::vector<Matrix> input = {
        {{0,0}},
        {{0,1}},
        {{1,0}},
        {{1,1}}
    };
    std::vector<Matrix> output = {
        {{0}},
        {{1}},
        {{1}},
        {{0}}
    };

    // layers
    FCLayer l1(2, 3);
    ActivationLayer l2(activation::tanh, activation::tanhPrime);
    FCLayer l3(3, 1);
    ActivationLayer l4(activation::tanh, activation::tanhPrime);

    // network
    Network network;
    network.addLayers({&l1, &l2, &l3, &l4});

    // train
    network.use(loss::mse, loss::msePrime);
    network.fit(input, output, 10000, 0.01);

    // test
    std::vector<Matrix> pred = network.predict(input);
    for(Matrix& p : pred) {
        std::cout << p << std::endl;
    }
    return 0;
}
