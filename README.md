# FT_LS

  리눅스 LS명령어 구현
  옵션: r(reverse), t(time), l(long format), R(recursive), a(all)

#### 사용된 구조체
struct dirent
  ```c
  struct dirent {
    __uint64_t  d_ino;           /* 항목의 파일 번호 */
    __uint64_t  d_seekoff;       /* seek 오프셋 (선택 사항, 서버에서 사용) */
    __uint16_t  d_reclen;        /* 이 레코드의 길이 */
    __uint16_t  d_namlen;        /* d_name에 있는 문자열의 길이 */
    __uint8_t   d_type;          /* 파일 유형, 아래 참조 */
    char        d_name[__DARWIN_MAXPATHLEN];  /* 항목 이름 (최대 MAXPATHLEN 바이트) */
  }
  ```
struct stat
  ```c
  struct stat {
    dev_t       st_dev;             /* 파일을 포함하는 장치의 ID */
    mode_t      st_mode;            /* 파일의 모드 (아래 참조) */
    nlink_t     st_nlink;           /* 하드 링크 수 */
    __darwin_ino64_t st_ino;        /* 파일 시리얼 번호 */
    uid_t       st_uid;             /* 파일의 사용자 ID */
    gid_t       st_gid;             /* 파일의 그룹 ID */
    dev_t       st_rdev;            /* 장치 ID */
    __DARWIN_STRUCT_STAT64_TIMES   /* 시간 정보*/ {
      struct timespec st_atimespec;           /* time of last access */ \
    	struct timespec st_mtimespec;           /* time of last data modification */ \
    	struct timespec st_ctimespec;           /* time of last status change */ \
    	struct timespec st_birthtimespec;       /* time of file creation(birth) */
    }
    off_t       st_size;            /* 파일 크기 (바이트 단위) */
    blkcnt_t    st_blocks;          /* 파일에 할당된 블록 수 */
    blksize_t   st_blksize;         /* I/O에 대한 최적의 블록 크기 */
    __uint32_t  st_flags;           /* 파일에 대한 사용자 정의 플래그 */
    __uint32_t  st_gen;             /* 파일 생성 번호 */
    __int32_t   st_lspare;          /* 예약됨: 사용하지 마세요! */
    __int64_t   st_qspare[2];       /* 예약됨: 사용하지 마세요! */
  ```

#### 구현
readdir을 이용해 파일 이름을 가져온 후 아래 규칙에 맞게 출력
  - 기본 : ascii순으로 파일 이름 출력
  - long format : stat을 이용해 파일 내용 출력

