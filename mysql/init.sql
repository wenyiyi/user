CREATE TABLE `user` (
  `id` bigint(20) NOT NULL COMMENT '主键id',
  `mobile` varchar(255) NOT NULL COMMENT '手机号，用于登录',
  `password` varchar(32) DEFAULT NULL COMMENT '加密密码'，
  `create_time` datetime(0) NULL COMMENT '创建时间',
  `update_time` datetime(0) NULL COMMENT '更新时间',
  PRIMARY KEY (`id`),
  UNIQUE INDEX `phone_idx`(`phone`) USING HASH,
  INDEX()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE `billing`.`Untitled`  (
  `id` bigint(20) NOT NULL COMMENT '主键id',
  `phone` varchar(255) NULL COMMENT '手机号',
  `token` varchar(255) NULL COMMENT '加密后的 token',
  `status` tinyint(3) NULL COMMENT '状态：0生效 1失效',
  `expire_time` datetime(0) NULL COMMENT '过期时间',
  `device` varchar(255) NULL COMMENT '设备号',
  `create_time` datetime(0) NULL COMMENT '创建时间',
  `update_time` datetime(0) NULL COMMENT '更新时间',
  PRIMARY KEY (`id`),
  UNIQUE INDEX `phone_idx`(`phone`) USING HASH,
  INDEX()
);
