////////////////////////////////////////////////////////////////////////
// COMP1521 19t2 ... course website
// COMP1521 19t3 ... course website

$(document).ready(function()
{
	function on_load()
	{
		annotate_man_pages();

		// Weekly Test code:
		if (get_start_time() !== null)
			start_test();
		else
			render_test_elements();
	}

	////////////////////////////////////////////////////////////////////

	const MAN_PATTERN = /^([^(]+)\(([^)]+)\)$/;

	/// Annotate manual page references of the form <cite>man(7)</cite>.
	///
	/// Students seem to very actively use this during labs, and the
	/// behaviour is described in a lab exercise in week 1 or 2.
	function annotate_man_pages()
	{
		document
			.querySelectorAll('cite')
			.forEach(
				x => {
					let text = x.innerText;
					let url = man_page_url(text);
					if (url != null) {
						/// show man section in () may confuse very weak students
						/// as it looks like a function call
						/// as compromise show man command with section in hover text
						let section = '';
						let bare_name = text;
						let m = text.match(/(.*)\((.*)\)/);
						if (m) {
							bare_name = m[1];
							section = m[2];
						}
						x.innerHTML = `<a title="man ${section} ${bare_name}" href="${url}">${bare_name}</a>`;
					}
				});
	}

	/// Given a man page reference, get a URL that documents it.
	function man_page_url(doc)
	{
		if (doc == null || !doc.match(MAN_PATTERN)) {
			return null;
		}
		let USE_FREEBSD_MAN = false;
		let USE_OPENBSD_MAN = false;
		/// use man7 pages better for COMP1521 if its not section 1
		/// are these really better than Debian?
		let USE_MAN7_MAN    = document.URL.match (/cs1521/) && !doc.match (/\(1/);
		let USE_POSIX_MAN   = false;

		if (USE_FREEBSD_MAN) return freebsd_man_page_url (doc);
		if (USE_OPENBSD_MAN) return openbsd_man_page_url (doc);
		if (USE_MAN7_MAN)    return man7_man_page_url (doc);
		if (USE_POSIX_MAN)   return posix_man_page_url (doc);
		
		// TODO: find some other man page sources
		// TODO: make the man page source selectable on the page

		// use Debian by default
		return debian_man_page_url (doc); // 

	}

	/// ... FreeBSD man pages are very thorough and extensive, though
	/// the renderer doesn't do a particularly pretty job.
	function freebsd_man_page_url(doc)
	{
		const FREEBSD_MAN_BASE = 'https://man.freebsd.org';
		return `${FREEBSD_MAN_BASE}/${doc}`;
	}

	/// ... OpenBSD man pages are fairly extensive and very nicely
	/// presented, though functions often have interesting paranoia
	/// improvements and therefore interfaces may not be quite right.
	function openbsd_man_page_url(doc)
	{
		const OPENBSD_MAN_BASE = 'https://man.openbsd.org';
		var [_, page, sect] = doc.match(MAN_PATTERN);
		return `${OPENBSD_MAN_BASE}/${page}.${sect}`;
	}

	/// ... Debian's man page collection is practically complete.
	function debian_man_page_url(doc)
	{
		const OPENBSD_MAN_BASE = 'https://manpages.debian.org';
		var [_, page, sect] = doc.match(MAN_PATTERN);
		return `${OPENBSD_MAN_BASE}/jump?q=${page}.${sect}`;
	}

	/// ... man7.org has a pretty good collection.
	function man7_man_page_url(doc)
	{
		const MAN7_MAN_BASE = 'http://man7.org/linux/man-pages';
		var [_, page, sect] = doc.match(MAN_PATTERN);
		return `${MAN7_MAN_BASE}/man${sect}/${page}.${sect}.html`;
	}

	/// ... POSIX.1 documentation.  Not the best coverage of utilities
	/// and exotic functions, but probably usable for most cases.
	function posix_man_page_url(doc)
	{
		const POSIX_MAN_BASE   = 'https://pubs.opengroup.org/onlinepubs/9699919799';
		var [_, page, sect] = doc.match(MAN_PATTERN);

		// we probably want to do some sort of 'does this exist' filtering...
		switch (sect) {
		case '1': case '6': case '8':
			return `${POSIX_MAN_BASE}/utilities/${page}.html`;
		case '2': case '3':
			return `${POSIX_MAN_BASE}/functions/${page}.html`;
		default:
			return null;
		}
	}

	////////////////////////////////////////////////////////////////////

	function run_cgi(base_url, cgi) {
		if (!cgi || cgi.length === 0)
			return;
		if (cgi.charAt(0) == "#")
			cgi = cgi.substr(1);
		if (cgi.length === 0)
			return;
		var cgi_output = $(".cgi_output_display")[0];
		var cgi_source = $(".cgi_source_display")[0];
		if (/insecure/.test(cgi)) {
			cgi_source.src = "";
		} else {
			cgi_output.src = base_url + cgi;
		}

		if (/\.html$/.test(cgi)) {
			cgi_source.src = "";
		} else {
			if (/insecure/.test(cgi)) {
				cgi_source.src = "";
			} else {
				cgi_output.src = base_url + cgi;
			}

			if (/\.html$/.test(cgi)) {
				cgi_source.src = "";
			} else {
				cgi_source.src = base_url + cgi + ".txt";
				console.log($('.title_panel'));
				$('.title_panel').text(cgi);
				$('.title_panel').append(' ');
				$('.title_panel').append($('<a>', {text: ' download', target: '_blank', href: base_url + cgi + ".txt"}));
				$('.title_panel').append(' ');
				$('.title_panel').append($('<a>', {text: ' run in new window', target: '_blank', href: base_url + cgi}));
			}
		}
	}

	function show_html_source(iframe) {
		var html_source = $(iframe).parent().parent().find(".html_source_display");
		if (!html_source.length) {
			html_source = $("#html_source");
		}
		var d = iframe.contentWindow.document;
		head_html = d.head.outerHTML.concat("\n");
		body_html = d.body.outerHTML.concat("\n");
		body_html = body_html.replace(/\s*<\/body>/mi, '\n<\/body>');
		html = head_html.concat(body_html);
		html = "<html>\n".concat(html).concat("<").concat("/html>\n");
		$(html_source).text(html);
	}

	////////////////////////////////////////////////////////////////////


	const TEST_READING_TIME = 5;  // minutes
	const TEST_WORKING_TIME = 60; // minutes
	const TEST_BEFORE = 0,
		  TEST_READING = 1,
		  TEST_WORKING = 2,
		  TEST_AFTER = 3;
	const TEST_QUESTION_HIDE
		  = "filter: blur(2rem); "
		  + "background-color: #eeeeee;"
		  + "border: 5px solid black;";

	function start_time_key() {
		let path_blob = btoa(window.location.pathname);
		return "starttime_" + path_blob;
	}

	function get_start_time() {
		return localStorage.getItem(start_time_key());
	}

	function timer_tick() {
		let start_time = get_start_time();
		render_test_elements();

		let state = get_test_state();
		switch (get_test_state()) {
		case TEST_READING:
		case TEST_WORKING:
			let time_now = Date.now() / 1000;
			let time_since_start = time_now - start_time;

			let reading_duration = (TEST_READING_TIME * 60);
			let working_duration = ((TEST_READING_TIME + TEST_WORKING_TIME) * 60);

			let reading_time = Math.floor((reading_duration - time_since_start) / 60);
			let working_time = Math.floor((working_duration - time_since_start) / 60);

			let test_body = document.getElementById('test-body');
			let test_time = test_body.getElementsByTagName('time')[0];
			let progress_reading = document.getElementById('test-progress-reading');
			let progress_working = document.getElementById('test-progress-working');

			let reading_percent = 0;
			if (get_test_state() === TEST_READING) {
				test_time.innerHTML = "" + reading_time;
				reading_percent = Math.min(reading_duration, time_since_start) / reading_duration * 100;
			} else if (get_test_state() === TEST_WORKING) {
				test_time.innerHTML = "" + working_time;
				reading_percent = reading_duration / working_duration * 100;
			}

			let working_percent = (time_since_start / working_duration * 100) - reading_percent;

			progress_reading.style.width = reading_percent + "%";
			progress_reading.attributes['aria-valuenow'] = reading_percent;
			progress_working.style.width = working_percent + "%";
			progress_working.attributes['aria-valuenow'] = working_percent;

			break;
		}

		setTimeout(timer_tick, 2000);
	}

	function start_test() {
		let start_time = get_start_time();
		if (start_time === null) {
			localStorage.setItem(start_time_key(), Date.now() / 1000);
			fetch('timestamp');
		}
		timer_tick();
	};

	function get_test_state() {
		let start_time = get_start_time();
		if (start_time === null)
			return TEST_BEFORE;

		let time_since_start = Date.now() / 1000 - start_time;

		if (time_since_start < TEST_READING_TIME * 60)
			return TEST_READING;
		if (time_since_start < (TEST_READING_TIME + TEST_WORKING_TIME) * 60)
			return TEST_WORKING;

		return TEST_AFTER;
	}

	function render_test_elements() {
		let clock = document.getElementById('test-clock');
		if (clock === null) return;

		let title  = document.getElementById('test-title');
		let body   = document.getElementById('test-body');
		let button = document.getElementById('test-button');
		let testQs = document.getElementById('questions');

		let progress = document.getElementById('test-progress-block');
		let progBar  = document.getElementById('test-progress');

		let title_inner, body_inner,
			show_button = false,
			show_progress = false,
			show_questions = false;
		switch (get_test_state()) {
		case TEST_BEFORE:
			title_inner = 'test-title-before';
			body_inner  = 'test-body-before';
			show_button = true;
			show_progress = false;
			show_questions = false;
			break;

		case TEST_READING:
			title_inner = 'test-title-reading';
			body_inner  = 'test-body-reading';
			show_progress = true;
			show_questions = true;
			break;

		case TEST_WORKING:
			title_inner = 'test-title-working';
			body_inner  = 'test-body-working';
			show_progress = true;
			show_questions = true;
			break;

		case TEST_AFTER:
			title_inner = 'test-title-after';
			body_inner  = 'test-body-after';
			show_progresss = true;
			show_questions = true;
			break;
		}

		title.innerHTML = document.getElementById(title_inner).innerHTML;
		body.innerHTML  = document.getElementById(body_inner).innerHTML;

		if (show_button) {
			button.style.display = 'block';
			button.onclick = start_test;
		} else {
			button.style.display = 'none';
		}

		if (show_progress) {
			progress.style.visibility = '';
		} else {
			progress.style.visibility = 'hidden';
		}

		if (show_questions) {
			testQs.style = '';
		} else {
			testQs.style = TEST_QUESTION_HIDE;
		}
	}

	////////////////////////////////////////////////////////////////////////

	return on_load();
});

////////////////////////////////////////////////////////////////////////
