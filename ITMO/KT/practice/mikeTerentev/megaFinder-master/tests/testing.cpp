//
// Created by Михаил Терентьев on 2018-12-21.
//
#include <tests/gtest/gtest.h>
#include <QObject>
#include <fileindexer.h>
#include <trigramsrepository.h>
#include <trigramssearcher.h>

const QString dir = "/Users/miketerentyev/itmo/2-year/MegaFinder/tests/test_dir/";

TEST(file_count_correctness, empty) {
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "count/empty", &repository, &watcher);
    searcher.indexDir();
    EXPECT_TRUE(repository.getTrigramData().size() == 1);
    EXPECT_TRUE(repository.getFilesAmount() == 0);
}

TEST(file_count_correctness, count_1_file) {
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "count/1-file", &repository, &watcher);
    searcher.indexDir();
    EXPECT_TRUE(repository.getTrigramData().size() == 1);
    EXPECT_TRUE(repository.getFilesAmount() == 1);
}

TEST(file_count_correctness, count_3_files) {
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "count/3-files", &repository, &watcher);
    searcher.indexDir();
    EXPECT_TRUE(repository.getTrigramData().size() == 1);
    EXPECT_TRUE(repository.getFilesAmount() == 3);
}

TEST(file_count_correctness, hidden_files) {
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "count/hidden-files", &repository, &watcher);
    searcher.indexDir();
    EXPECT_TRUE(repository.getTrigramData().size() == 1);
    EXPECT_TRUE(repository.getFilesAmount() == 0);
}


TEST(file_count_correctness, count_tree) {
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "count/", &repository, &watcher);
    searcher.indexDir();
    EXPECT_TRUE(repository.getTrigramData().size() == 1);
    EXPECT_TRUE(repository.getFilesAmount() == 4);
}

TEST(permission_check, no_permission) {
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "no-permission/", &repository, &watcher);
    searcher.indexDir();
    EXPECT_TRUE(repository.getFilesAmount() == 0);
}

TEST(indexer_check, three_character) {
    FileIndexer indexer;
    QSet<uint64_t> result = indexer.findTrigramsOfFile(dir + "hash-checker/1-trigram/1-trigram.txt");
    EXPECT_EQ(*(result.begin()), 5064013);
    EXPECT_TRUE(result.size() == 1);
}

TEST(indexer_check, three_diff_trigrams) {
    FileIndexer indexer;
    QSet<uint64_t> result = indexer.findTrigramsOfFile(dir + "hash-checker/3-different/3-different.txt");
    QSet<uint64_t> answer = {5064013, 4541761, 5062979};
    EXPECT_TRUE(result.size() == 3);
    for (auto item : result) {
        EXPECT_TRUE(answer.contains(item));
    }
}

TEST(indexer_check, two_pairs) {
    FileIndexer indexer;
    QSet<uint64_t> result = indexer.findTrigramsOfFile(dir + "hash-checker/2same/2same.txt");
    QSet<uint64_t> answer = {4541765, 5064013};
    EXPECT_TRUE(result.size() == 2);
    for (auto item : result) {
        EXPECT_TRUE(answer.contains(item));
    }
}

TEST(finder_check, three_diff_trigrams) {
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "hash-checker/3-different/", &repository, &watcher);
    searcher.indexDir();
    auto res = repository.find("MAC");
    EXPECT_TRUE(res.size() == 1);
    EXPECT_TRUE(res[0].second.size() == 1);
    res = repository.find("EM");
    EXPECT_TRUE(res.size() == 1);
    EXPECT_TRUE(res[0].second.size() == 1);
    res = repository.find("AC");
    EXPECT_TRUE(res.size() == 1);
    EXPECT_TRUE(res[0].second.size() == 1);
}

TEST(finder_check, three_character) {
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "hash-checker/1-trigram/", &repository, &watcher);
    searcher.indexDir();
    auto res = repository.find("M");
    EXPECT_TRUE(res.size() == 1);
    EXPECT_TRUE(res[0].second.size() == 1);
    res = repository.find("ME");
    EXPECT_TRUE(res.size() == 1);
    EXPECT_TRUE(res[0].second.size() == 1);
    res = repository.find("MEM");
    EXPECT_TRUE(res.size() == 1);
    EXPECT_TRUE(res[0].second.size() == 1);
    res = repository.find("EM");
    EXPECT_TRUE(res.size() == 1);
    EXPECT_TRUE(res[0].second.size() == 1);
}

TEST(finder_check, several) {
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "hash-checker/", &repository, &watcher);
    searcher.indexDir();
    auto res = repository.find("M");
    EXPECT_TRUE(res[0].second.size() == 3);
    res = repository.find("AC");
    EXPECT_TRUE(res[0].second.size() == 1);
    res = repository.find("MEMAC");
    EXPECT_TRUE(res[0].second.size() == 1);
    res = repository.find("MEM");
    EXPECT_TRUE(res[0].second.size() == 3);
}

TEST(remove,remove){
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "count", &repository, &watcher);
    searcher.indexDir();
    searcher.removeDirectory();
    EXPECT_TRUE(repository.getTrigramData().empty());
}

TEST(easy, empty) {
    TrigramsRepository repository;
    QFileSystemWatcher watcher;
    TrigramsSearcher searcher(dir + "empty", &repository, &watcher);
    searcher.indexDir();
    EXPECT_TRUE(searcher.getData().isEmpty());
}



