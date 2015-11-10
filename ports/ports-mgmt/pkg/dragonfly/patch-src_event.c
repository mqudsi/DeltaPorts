--- src/event.c.orig	2015-09-07 14:04:22 UTC
+++ src/event.c
@@ -547,6 +547,7 @@ event_callback(void *data, struct pkg_ev
 	int *debug = data;
 	struct pkg_event_conflict *cur_conflict;
 	const char *filename;
+	char trunc_filename[42] = { 0 };
 
 	if (msg_buf == NULL) {
 		msg_buf = sbuf_new_auto();
@@ -604,9 +605,12 @@ event_callback(void *data, struct pkg_ev
 			 */
 			filename = ev->e_fetching.url;
 		}
+		strncpy(trunc_filename, filename, 41);
+		if (strnlen(filename,42) > 41)
+			trunc_filename[40] = '*';
 		job_status_begin(msg_buf);
 		progress_debit = true;
-		sbuf_printf(msg_buf, "Fetching %s", filename);
+		sbuf_printf(msg_buf, "%-41s", trunc_filename);
 
 		break;
 	case PKG_EVENT_FETCH_FINISHED:
