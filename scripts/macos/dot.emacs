(require 'package)
(setq package-archives '(("melpa" . "https://melpa.org/packages/")
                         ("org" . "https://orgmode.org/elpa/")) )
(when (< emacs-major-version 24)
  ;; For important compatibility libraries like cl-lib
  (add-to-list 'package-archives '("gnu" . "https://elpa.gnu.org/packages/")))
(package-initialize)
(require 'use-package)

(add-hook 'c-mode-common-hook
          '(lambda ()
             (c-set-style "stroustrup")
             (setq c-basic-offset 4)
             (setq tab-width 4)
             (setq indent-tabs-mode nil)))

(add-hook 'c++-mode-hook
	  '(lambda ()
	     (c-set-style "stroustrup")
             (setq c-basic-offset 4)
             (setq tab-width 4)
	     (setq indent-tabs-mode nil)))

(add-hook 'c++-mode-hook 'rtags-start-process-unless-running)

(add-hook 'sh-mode-hook
          '(lambda ()
             (setq tab-width 4)
             (setq indent-tabs-mode t)))

(setq split-height-threshold 0)
(setq split-width-threshold 0)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
(add-to-list 'exec-path (expand-file-name "/usr/local/bin")) ;; path to rdm/rc
(add-to-list 'load-path (expand-file-name "/usr/local/share/emacs/site-lisp/rtags")) ;; path to rtags.el

(use-package rtags
  :config
  (setq rtags-autostart-diagnostics t)
  (rtags-diagnostics)
  (setq rtags-completions-enabled t)
  (rtags-enable-standard-keybindings))

(use-package company)
(use-package company-rtags)
(push 'company-rtags company-backends)
(global-company-mode)
(define-key c-mode-base-map (kbd "<C-tab>") (function company-complete))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(use-package langtool
  :config
  (setq langtool-language-tool-jar "/opt/LanguageTool-3.8/languagetool-commandline.jar")
  (setq langtool-default-language "en-US"))

;;;;;;;;;;;;;;
(use-package mozc
  :config
  (set-language-environment "Japanese")
  (setq default-input-method "japanese-mozc")
  (prefer-coding-system 'utf-8))

;;;;; org-mode ;;;;;
(use-package org
  :config
  (define-key global-map "\C-cl" 'org-store-link)
  (define-key global-map "\C-ca" 'org-agenda)
  (setq org-log-done t))

(add-hook 'org-mode-hook
          '(lambda ()
             (local-set-key "\M-\C-g" 'org-plot/gnuplot)))

(setq org-agenda-files (list "~/org/todo.org"))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
'(default ((t (:height 140 :family "Consolas"))))

;;
(setq browse-url-browser-function 'browse-url-generic)
(setq browse-url-generic-program 
      (if (file-exists-p "/usr/bin/chromium")
          "/usr/bin/chromium" "/usr/bin/google-chrome"))

(add-to-list 'auto-mode-alist '("\\.plt\\'" . gnuplot-mode))
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(custom-enabled-themes (quote (deeper-blue)))
 '(package-selected-packages
   (quote
    (mozc-im company-rtags rtags cuda-mode langtool flycheck wc-mode vhdl-tools magit irony-eldoc gnuplot-mode gnuplot flycheck-irony company-irony cmake-font-lock auto-complete-c-headers))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )