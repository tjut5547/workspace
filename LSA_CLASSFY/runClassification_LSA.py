#-*- coding:utf-8 -*-
#!/usr/bin/env python

import pickle
import getopt, sys
import os, time, jieba, jieba.analyse

from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.decomposition import TruncatedSVD
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import Normalizer
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split

def get_stop_words(Path):
    with open(Path, 'r') as fd:
        stop_words = fd.read().split()
    return stop_words

def usage():
    print ("THIS IS JUST FOR FUN, IF YOU ARE TOO SERIOUS, YOU LOSE")
    print ('\n^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^')
    print ('\n仅仅支持一个参数，loading_pickle 为1则从data.pickle当中获取数据，否则读取文件')
    print ('\n^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^')
    print ("\nTHIS IS JUST FOR FUN, IF YOU ARE TOO SERIOUS, YOU LOSE")

def get_opt_for_loading_dataset():
    global loading_pickle
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'hl:', ['loading_pickle='])
    except:
        sys.exit(1)
    
    if len(opts) > 1:
        print ("TOO MANY PARAM")
        sys.exit(1)
    if len(opts) == 0:
        loading_pickle = 1
        return

    for opt, arg in opts:
        if opt == '-h':
            usage()
            loading_pickle = 1
            sys.exit(2)
        elif opt in ['-l', '--loading_pickle']:
            loading_pickle = 1
        elif opt in ['-r', '--readingFile']:
            loading_pickle = 0
        else:
            print ("传入参数错误！！！！！！！！！")
            sys.exit(3)

def delete_and_split(stop_words):
    for index in range(len(all_context)):
        ans = ''
        for word in list(jieba.cut(all_context[index])):
            ans = ans + word + ' '
        all_context[index] = ans     

def loading_dataset(Path, stopwords):
    if loading_pickle == 1:
        raw_text_dataset = pickle.load(open( "data/data.pickle", "rb" ))
        train_context = raw_text_dataset[0] # 训练文本
        train_labels = raw_text_dataset[1] # 训练文本标签
        test_context = raw_text_dataset[2] # 测试文本
        test_labels = raw_text_dataset[3] # 测试文本标签
    else:
        global all_context
        all_context = []; all_labels = []
        all_dirtory = os.listdir(Path)
        for dirtory in all_dirtory:
            all_file = os.listdir(os.path.join(Path, dirtory))
            print ("路径 = ", dirtory, time.asctime((time.localtime(time.time()))))
            for file in all_file:
                with open(os.path.join(Path, dirtory, file), 'r') as fd:
                    context = fd.read()
                all_context.append(context); all_labels.append(dirtory)
        print ("****START******\t", time.asctime((time.localtime(time.time()))))
        delete_and_split(stopwords)
        print ("****END******\t", time.asctime((time.localtime(time.time()))))
        train_context, test_context, train_labels, test_labels = train_test_split(all_context, all_labels, test_size = 0.2)
        pickle.dump((train_context, train_labels, test_context, test_labels), open("data/data.pickle", "wb"))
    return train_context, train_labels, test_context, test_labels

def train_and_get_lsa(train_context, test_context):
    vectorizer = TfidfVectorizer(max_df=0.5, max_features=5000, min_df=2, use_idf=True, lowercase=False, decode_error='ignore', analyzer=str.split)
    train_tfidf = vectorizer.fit_transform(train_context)
    svd = TruncatedSVD(100)
    lsa = make_pipeline(svd, Normalizer(copy=False))
    lsa_train = lsa.fit_transform(train_tfidf)

    # explained_variance = svd.explained_variance_ratio_.sum()
    # print("  Explained variance of the SVD step: {}%".format(int(explained_variance * 100)))

    test_tfidf = vectorizer.transform(test_context)
    lsa_test = lsa.transform(test_tfidf)
    return train_tfidf, test_tfidf, lsa_train, lsa_test

# def classify_tfidf(train_tfidf, train_labels_double, test_tfidf, test_lables_double):
def classify_tfidf(train_tfidf, train_labels, test_tfidf, test_labels):
    knn_tfidf = KNeighborsClassifier(n_neighbors=5, algorithm='brute', metric='cosine')
    knn_tfidf.fit(train_tfidf, train_labels)

    p = knn_tfidf.predict(test_tfidf)
    # Measure accuracy
    numRight = 0;
    for i in range(0,len(p)):
        if p[i] == test_labels[i]:
            numRight += 1
    return (float(numRight) / float(len(test_labels)) * 100.0)

# def classify_tf_idf_lsa(lsa_train, train_labels_double, lsa_test, test_lables_double):
def classify_tf_idf_lsa(lsa_train, train_labels, lsa_test, test_labels):
    knn_lsa = KNeighborsClassifier(n_neighbors=5, algorithm='brute', metric='cosine')
    knn_lsa.fit(lsa_train, train_labels)
    p = knn_lsa.predict(lsa_test)
    # Measure accuracy
    numRight = 0;
    for i in range(0,len(p)):
        if p[i] == test_labels[i]:
            numRight += 1
    return float(numRight) / float(len(test_labels)) * 100.0

if __name__ == '__main__':
    print ("START TIME : ", time.asctime((time.localtime(time.time()))))
    get_opt_for_loading_dataset()
    stop_words = get_stop_words ('stopwords.txt')
    train_context, train_labels, test_context, test_labels = loading_dataset('文档', stop_words)
    print ("END OF LOADING DATA TIME : ", time.asctime((time.localtime(time.time()))))
    train_tfidf, test_tfidf, lsa_train, lsa_test = train_and_get_lsa(train_context, test_context)
    print ("END OF GET TFIDF AND LSA TIME : ", time.asctime((time.localtime(time.time()))))
    accuracy_tfidf = classify_tfidf(train_tfidf, train_labels, test_tfidf, test_labels)
    print ("END OF CLASSIFY TFIDF TIME : ", time.asctime((time.localtime(time.time()))))
    accuracy_lsa = classify_tf_idf_lsa(lsa_train, train_labels, lsa_test, test_labels)
    print ("END OF CLASSIFY LSA TIME : ", time.asctime((time.localtime(time.time()))))
    print ("ACCURACY ABOUT TFIDF IS : %f" % (accuracy_tfidf))
    print ("ACCURACY ABOUT LSA IS : %f" % (accuracy_lsa))