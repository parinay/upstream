From 66430ae381add9095d421887a4cf63fbe7f71407 Mon Sep 17 00:00:00 2001
From: Parinay Kondekar <parinay.kondekar@seagate.com>
Date: Sun, 6 Dec 2015 23:33:17 +0530
Subject: [PATCH] LU-6518 obd: Unhandled possible allocation failure in
 lustre_start_mgc

Patch to handle un-handled possible allocation failure
of struct obd_uuid.

Change-Id: Ib19d4c53a6dae5e2f6a80e0fdf755fa7aac81fd1
Signed-off-by: Parinay Kondekar <parinay.kondekar@seagate.com>
Reviewed-on: http://review.whamcloud.com/17493
Tested-by: Jenkins
Reviewed-by: Dmitry Eremin <dmitry.eremin@intel.com>
Reviewed-by: Frank Zago <fzago@cray.com>
Tested-by: Maloo <hpdd-maloo@intel.com>
Reviewed-by: Oleg Drokin <oleg.drokin@intel.com>
---
 lustre/obdclass/obd_mount.c | 3 +++
 1 file changed, 3 insertions(+)

diff --git a/lustre/obdclass/obd_mount.c b/lustre/obdclass/obd_mount.c
index 6b1ae94fc2..3aa9d28bfd 100644
--- a/lustre/obdclass/obd_mount.c
+++ b/lustre/obdclass/obd_mount.c
@@ -398,6 +398,9 @@ int lustre_start_mgc(struct super_block *sb)
 
         /* Random uuid for MGC allows easier reconnects */
         OBD_ALLOC_PTR(uuid);
+	if (uuid == NULL)
+		GOTO(out_free, rc = -ENOMEM);
+
         ll_generate_random_uuid(uuidc);
         class_uuid_unparse(uuidc, uuid);
 
-- 
2.17.1

