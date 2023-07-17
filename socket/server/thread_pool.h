#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <QObject>
#include <QMutex>
#include <QQueue>
#include <QThreadPool>
#include <QRunnable>
#include <QtConcurrent/QtConcurrent>
#include <QWaitCondition>
#include <functional>

class ThreadPool : public QObject
{
    Q_OBJECT

public:
    explicit ThreadPool(QObject *parent = nullptr)
        : QObject(parent)
    {
        m_threadPool.setMaxThreadCount(4); // 设置线程池中的最大线程数
    }

    ~ThreadPool()
    {
        shutdown();
    }

    template <typename F, typename... Args>
    void submit(F &&f, Args &&...args)
    {
        // 创建一个继承自 QRunnable 的任务类，用于执行具体的函数
        class Task : public QRunnable
        {
        public:
            Task(F &&func, Args &&...args)
                : m_func(std::bind(std::forward<F>(func), std::forward<Args>(args)...))
            {
            }

            void run() override
            {
                m_func(); // 执行函数
            }

        private:
            std::function<void()> m_func; // 存储要执行的函数
        };

        // 创建任务对象并添加到线程池中执行
        Task *task = new Task(std::forward<F>(f), std::forward<Args>(args)...);
        connect(task, &Task::finished, task, &Task::deleteLater); // 连接任务完成信号，自动释放任务对象
        m_threadPool.start(task);
    }

    void shutdown()
    {
        m_threadPool.clear(); // 清除线程池中的所有任务
        m_threadPool.waitForDone(); // 等待所有线程执行完成
    }

private:
    QThreadPool m_threadPool;
};

#endif // THREADPOOL_H

