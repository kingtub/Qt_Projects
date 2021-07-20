#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include<QString>
class Constants {
    //内网测试 http://192.168.1.241
    //内网开发 http://192.168.1.181
    //外网预发布 https://ngpre.zr66.com
public:
    static inline QString get_domain_url() {
        return "http://192.168.1.241";
        //return "https://ngpre.zr66.com";
    }
};

#endif // CONSTANTS_HPP
