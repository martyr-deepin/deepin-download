#ifndef OPTIONSTRUCT_H
#define OPTIONSTRUCT_H
#include <QString>

struct changeOption{

   QString bt_max_peers; //默认：plain
   QString bt_request_peer_speed_limit; //默认：50K
   QString bt_remove_unselected_file; //默认：false
   QString force_save; // 默认：false
   QString max_download_limit; //默认：0
   QString max_upload_limit; // 默认：0

};

struct changeGlobalOption{

   QString bt_max_open_files; // 指定要在多文件BitTorrent / Metalink全局下打开的最大文件数。默认：100
   QString download_result;
   QString keep_unfinished_download_result; //默认：true
   QString log;          //日志文件的文件名
   QString log_level;    //LEVEL或者是debug，info，notice，warn或error。默认：debug
   QString max_concurrent_downloads;    //为每个队列项设置最大并行下载数。
   QString max_download_result;         //设置内存中保存的最大下载结果数。
   QString max_overall_download_limit;  //设置最大总体下载速度（以字节/秒为单位）
   QString max_overall_upload_limit;    //设置最大总体上传速度（以字节/秒为单位）
   QString optimize_concurrent_downloads;  //根据可用带宽优化并发下载次数 默认：false
   QString save_cookies;   //将Cookie保存到Mozilla / Firefox（1.x / 2.x）/ Netscape 格式的文件中。
   QString save_session;   //退出时将错误/未完成的下载保存到文件
   QString server_stat_of; //指定保存服务器性能配置文件的文件名

};

struct Option {

    QString allow_overwrite;   //false
    QString allow_piece_length_change;  //false
    QString always_resume; // true
    QString async_dns; // true
    QString auto_file_renaming; // true
    QString bt_enable_hook_after_hash_check; // true
    QString bt_enable_lpd; // false
    QString bt_force_encryption; // false
    QString bt_hash_check_seed; // true
    QString bt_max_peers; // 55
    QString bt_metadata_only; // false
    QString bt_min_crypto_level; // plain
    QString bt_remove_unselected_file; // false
    QString bt_request_peer_speed_limit; // 51200
    QString bt_require_crypto; // false
    QString bt_save_metadata; // false
    QString bt_seed_unverified; // false
    QString bt_stop_timeout; // 0
    QString bt_tracker_connect_timeout; // 60
    QString bt_tracker_interval; // 0
    QString bt_tracker_timeout; // 60
    QString check_integrity; // false
    QString conditional_get; // false
    QString connect_timeout; // 60
    QString content_disposition_default_utf8; // false
    QString _continue; // true
    QString dir; // /home/gaochong/Desktop
    QString dry_run; // false
    QString enable_http_keep_alive; // true
    QString enable_http_pipelining; // ",\"jsonrpc\":\"2.0\",\"result\":{\"bitfield\":\"fffffff00000000000\",\"completedLength\":\"30048256\",\"connections\":\"1\",\"dir\":\"\\/home\\/gaochong\\/Desktop\",\"downloadSpeed\":\"879024\",\"files\":[{\"completedLength\":\"29360128\",\"index\":\"1\",\"length\":\"71154592\",\"path\":\"\\/home\\/gaochong\\/Desktop\\/QQ_8.9.5.22062_setup.exe\",\"selected\":\"true\",\"uris\":[{\"status\":\"used\",\"uri\":\"http:\\/\\/sw.bos.baidu.com\\/sw-search-sp\\/software\\/16d5a98d3e034\\/QQ_8.9.5.22062_setup.exe\"},{\"status\":\"waiting\",\"uri\":\"http:\\/\\/sw.bos.baidu.com\\/sw-search-sp\\/software\\/16d5a98d3e034\\/QQ_8.9.5.22062_setup.exe\"}]}],\"gid\":\"793331d96ab7a512\",\"numPieces\":\"68\",\"pieceLength\":\"1048576\",\"status\":\"active\",\"totalLength\":\"71154592\",\"uploadLength\":\"0\",\"uploadSpeed\":\"0\"}}"false
    QString enable_mmap; // false
    QString enable_peer_exchange; // true
    QString file_allocation; // prealloc
    QString follow_metalink; // true
    QString follow_torrent; // true
    QString force_save; // false
    QString ftp_pasv; // true
    QString ftp_reuse_connection; // true
    QString ftp_type; // binary
    QString hash_check_only; // false
    QString http_accept_gzip; // false
    QString http_auth_challenge; // false
    QString http_no_cache; // false
    QString lowest_speed_limit; // 0
    QString max_connection_per_server; // 1
    QString max_download_limit; // 0
    QString max_file_not_found; // 0
    QString max_mmap_limit; // 9223372036854775807
    QString max_resume_failure_tries; // 0
    QString max_tries; // 5
    QString max_upload_limit; // 0
    QString metalink_enable_unique_protocol; // true
    QString metalink_preferred_protocol; // none
    QString min_split_size; // 20971520
    QString no_file_allocation_limit; // 5242880
    QString no_netrc; // false
    QString parameterized_uri; // false
    QString pause_metadata; // false
    QString piece_length; // 1048576
    QString proxy_method; // get
    QString realtime_chunk_checksum; // true
    QString remote_time; // false
    QString remove_control_file; // false
    QString retry_wait; // 0
    QString reuse_uri; // true
    QString rpc_save_upload_metadata; // true
    QString save_not_found; // true
    QString seed_ratio; // 1.0
    QString split; // 5
    QString stream_piece_selector; // default
    QString timeout; // 60
    QString uri_selector; // feedback
    QString use_head; // false
    QString user_agent; // aria2/1.32.0

};

struct GlobalOption {

    QString allow_overwrite; // false
    QString allow_piece_length_change; // false
    QString always_resume; // true
    QString async_dns; // true
    QString auto_file_renaming; // true
    QString auto_save_interval; // 60
    QString bt_detach_seed_only; // false
    QString bt_enable_hook_after_hash_check; // true
    QString bt_enable_lpd; // false
    QString bt_force_encryption; // false
    QString bt_hash_check_seed; // true
    QString bt_max_open_files; // 100
    QString bt_max_peers; // 55
    QString bt_metadata_only; // false
    QString bt_min_crypto_level; // plain
    QString bt_remove_unselected_file; // false
    QString bt_request_peer_speed_limit; // 51200
    QString bt_require_crypto; // false
    QString bt_save_metadata; // false
    QString bt_seed_unverified; // false
    QString bt_stop_timeout; // 0
    QString bt_tracker_connect_timeout; // 60
    QString bt_tracker_interval; // 0
    QString bt_tracker_timeout; // 60
    QString ca_certificate; // /etc/ssl/certs/ca_certificates.crt
    QString check_certificate; // false
    QString check_integrity; // false
    QString conditional_get; // false
    QString conf_path; // /home/gaochong/.config/aria2/aria2.conf
    QString connect_timeout; // 60
    QString console_log_level; // notice
    QString content_disposition_default_utf8; // false
    QString _continue; // true
    QString daemon; // false
    QString deferred_input; // false
    QString dht_file_path; // /home/gaochong/.cache/aria2/dht.dat
    QString dht_file_path6; // /home/gaochong/.cache/aria2/dht6.dat
    QString dht_listen_port; // 6881_6999
    QString dht_message_timeout; // 10
    QString dir; // /home/gaochong/Desktop
    QString disable_ipv6; // true
    QString disk_cache; // 16777216
    QString download_result; // default
    QString dry_run; // false
    QString dscp; // 0
    QString enable_color; // true
    QString enable_dht; // true
    QString enable_dht6; // false
    QString enable_http_keep_alive; // true
    QString enable_http_pipelining; // false
    QString enable_mmap; // false
    QString enable_peer_exchange; // true
    QString enable_rpc; // true
    QString event_poll; // epoll
    QString file_allocation; // prealloc
    QString follow_metalink; // true
    QString follow_torrent; // true
    QString force_save; // false
    QString ftp_pasv; // true
    QString ftp_reuse_connection; // true
    QString ftp_type; // binary
    QString hash_check_only; // false
    QString help; // #basic
    QString http_accept_gzip; // false
    QString http_auth_challenge; // false
    QString http_no_cache; // false
    QString human_readable; // true
    QString keep_unfinished_download_result; // true
    QString listen_port; // 6881_6999
    QString log_level; // debug
    QString lowest_speed_limit; // 0
    QString max_concurrent_downloads; // 5
    QString max_connection_per_server; // 1
    QString max_download_limit; // 0
    QString max_download_result; // 1000
    QString max_file_not_found; // 0
    QString max_mmap_limit; // 9223372036854775807
    QString max_overall_download_limit; // 524288
    QString max_overall_upload_limit; // 0
    QString max_resume_failure_tries; // 0
    QString max_tries; // 5
    QString max_upload_limit; // 0
    QString metalink_enable_unique_protocol; // true
    QString metalink_preferred_protocol; // none
    QString min_split_size; // 20971520
    QString min_tls_version; // TLSv1
    QString netrc_path; // /home/gaochong/.netrc
    QString no_conf; // false
    QString no_file_allocation_limit; // 5242880
    QString no_netrc; // false
    QString optimize_concurrent_downloads; // false
    QString parameterized_uri; // false
    QString pause_metadata; // false
    QString peer_id_prefix; // A2_1_32_0_
    QString piece_length; // 1048576
    QString proxy_method; // get
    QString quiet; // false
    QString realtime_chunk_checksum; // true
    QString remote_time; // false
    QString remove_control_file; // false
    QString retry_wait; // 0
    QString reuse_uri; // true
    QString rlimit_nofile; // 1024
    QString rpc_allow_origin_all; // false
    QString rpc_listen_all; // false
    QString rpc_listen_port; // 6800
    QString rpc_max_request_size; // 2097152
    QString rpc_save_upload_metadata; // true
    QString rpc_secure; // false
    QString save_not_found; // true
    QString save_session; // /home/gaochong/aria2c.cache
    QString save_session_interval; // 0
    QString seed_ratio; // 1.0
    QString server_stat_timeout; // 86400
    QString show_console_readout; // true
    QString show_files; // false
    QString socket_recv_buffer_size; // 0
    QString split; // 5
    QString stderr; // false
    QString stop; // 0
    QString stream_piece_selector; // default
    QString summary_interval; // 60
    QString timeout; // 60
    QString truncate_console_readout; // true
    QString uri_selector; // feedback
    QString use_head; // false
    QString user_agent; // aria2/1.32.0

};


#endif // OPTIONSTRUCT_H
