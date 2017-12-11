from sklearn.linear_model import *
from sklearn.externals import joblib

# network = SGDClassifier(alpha=0.0001, average=False, epsilon=0.05, eta0=0.0025,
#         fit_intercept=False, l1_ratio=0.10, learning_rate='optimal', power_t=0.05,
#         random_state=None, shuffle=True, tol=None, warm_start=False,
#         verbose=True, loss='modified_huber', penalty='l2', max_iter=sgd_maxiter, n_jobs=-1)

def load_networkfile(network_file):
    print("[Python] Loading network file...")
    # Creates an SGDRegressor object with the same network values as contained in network_file
    network = joblib.load(network_file)
    return network

def get_prediction(network, input):
    # print("[Python] SKLReceivedInput: %s" % input)
    return network.predict(input)[0]
