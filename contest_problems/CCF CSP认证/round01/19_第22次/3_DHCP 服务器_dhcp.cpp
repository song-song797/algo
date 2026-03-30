/*
 * DHCP 服务器 (dhcp)
 * CCF CSP 第22次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
struct IP{
    string owner="";
    int state=0;
    int end_time=0;
};
void manage_discover(string& send,string& H,vector<IP>& ips,int et,int t,int T_def,int T_max,int T_min){
    int ip1=0, ip2=0, ip3=0;
    for (int i = 1; i <= ips.size()-1;i++){
      if(ips[i].owner==send&& ip1 == 0){
          ip1 = i;
      }
      if(ips[i].state==0&&ip2==0){
          ip2 = i;
      }
      if(ips[i].state==3&&ip3==0){
          ip3 = i;
      }
    }
    int ip=0;
    if(ip1!=0){
      ip = ip1;
    }
    if(ip2!=0&&ip==0){
      ip = ip2;
    }
    if(ip3!=0&&ip==0){
      ip = ip3;
    }
    if(ip==0)
        return;
    ips[ip].state = 1;
    ips[ip].owner = send;
    if(et==0){
        ips[ip].end_time = t + T_def;
    }else{
        int tt = max(et, t + T_min); 
        tt = min(tt, t + T_max);
        ips[ip].end_time = tt;
    }
    cout << H << ' ' << send << ' ' << "OFR" << ' ' << ip << ' ' << ips[ip].end_time << '\n';
}
void manage_request(string& get,string& send,string& H,vector<IP>& ips,int ip,int et,int t,int T_def,int T_max,int T_min){
    if(get!=H){
        for (int i = 1; i <= ips.size() - 1;i++){
            if(ips[i].owner==send&&ips[i].state==1){
                ips[i].state = 0;
                ips[i].owner = "";
                ips[i].end_time = 0;
            }
        }
        return;
    }else{
       if((ip<1||ip>ips.size()-1)||ips[ip].owner!=send){
          cout << H << ' ' << send << ' ' << "NAK" << ' ' << ip << ' ' << 0 << '\n';
          return;
       }else{
          ips[ip].state = 2;
          if(et==0){
              ips[ip].end_time = t + T_def;
          }else{
              int tt = max(et, t + T_min); 
              tt = min(tt, t + T_max);
              ips[ip].end_time = tt;
          }
       }
       cout << H << ' ' << send << ' ' << "ACK" << ' ' << ip << ' ' << ips[ip].end_time << '\n';
       return;
    }
}
void update_time(vector<IP>& ips, int t){
    for (int i = 1; i <= ips.size() - 1; i++){
        if(ips[i].end_time > 0 && ips[i].end_time <= t){
            if(ips[i].state == 1){ 
                ips[i].state = 0;
                ips[i].owner = "";
                ips[i].end_time = 0;
            } else if (ips[i].state == 2) { 
                ips[i].state = 3;
                ips[i].end_time = 0;
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, T_def, T_max, T_min;
    string H;
    cin >> N >> T_def >> T_max >> T_min >> H;
    vector<IP> ips(N+1);
    int n;
    cin >> n;
    while(n--){
        int t,ip,end_time;
        string send, get, type;
        cin >> t >> send >> get >> type >> ip >> end_time;
        update_time(ips, t);
        if(get!=H&&get!="*"&&type!="REQ"){
            continue;
        }
        if(type!="DIS"&&type!="REQ"){
            continue;
        }
        if(get=="*"&&type!="DIS"||get==H&&type=="DIS"){
            continue;
        }
        if(type=="DIS"){
            manage_discover(send, H, ips, end_time, t, T_def, T_max, T_min);
        }
        if(type=="REQ"){
            manage_request(get, send, H, ips, ip, end_time, t, T_def, T_max, T_min);
        }
    }
    return 0;
}
