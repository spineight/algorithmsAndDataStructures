# Using `git-annex` for Managing Large Files

This guide explains how to use `git-annex` for managing large files, based on the commands executed so far. It also includes instructions for ensuring redundancy by storing files on two external hard drives.

---

## 1. Install and Initialize `git-annex`

### Install `git-annex`:
Make sure `git-annex` is installed on your system. On most Linux distributions, you can Install git-annex
```bash
# For Fedora
sudo dnf install git-annex
```
Initialize git-annex in the repository
```bash
cd /home/oleg/dev/algorithmsAndDataStructures
git annex init "Video Management"
```

## 2. Add a File to `git-annex` Without Copying It Locally

If the file already exists on an external hard drive, you can add it to `git-annex` without copying it to your local repository. Use the `addurl` command:
```bash
git annex addurl file:///run/media/oleg/Kotyamba/ITMO/BaseAlgsForSchoolStudents/lec2_sorting_and_search \
  --file=90_sources_archive/videos/BaseAlgsForSchoolStudents/lec2_sorting_and_search
```
This creates a reference to the file in your repository without storing the file locally.

---

## 3. Add External Hard Drives as Remotes

To store files on external hard drives, you need to add them as remotes. Use the `initremote` command:

### Add the First Hard Drive:
```bash
git annex initremote Kotyamba type=directory directory=/run/media/oleg/Kotyamba encryption=none
```

### Add the Second Hard Drive:
```bash
git annex initremote Kotyamba2 type=directory directory=/run/media/oleg/Kotyamba2 encryption=none
```
These commands configure `git-annex` to use the specified directories on the external hard drives as storage locations.

---

## 4. Set Redundancy (Number of Copies)

To ensure redundancy, configure `git-annex` to maintain at least two copies of each file:
```bash
git annex numcopies 2
```
This tells `git-annex` to ensure that every file is stored on at least two remotes.

---

## 5. Copy Files to Both External Hard Drives

To copy a file to both external hard drives (Kotyamba and Kotyamba2), use the `copy` command:

### Copy to the First Hard Drive:
```bash
git annex copy 90_sources_archive/videos/BaseAlgsForSchoolStudents/lec2_sorting_and_search --to=Kotyamba
```

### Copy to the Second Hard Drive:
```bash
git annex copy 90_sources_archive/videos/BaseAlgsForSchoolStudents/lec2_sorting_and_search --to=Kotyamba2
```

These commands ensure that the file is stored on both hard drives, providing redundancy.

---

## 6. Verify File Locations

To check where the file is stored, use the `whereis` command:
```bash
git annex whereis 90_sources_archive/videos/BaseAlgsForSchoolStudents/lec2_sorting_and_search
```
This will show all the remotes where the file is currently stored.

---

## Summary of Commands:
1. Initialize `git-annex`:
   ```bash
   git annex init
   ```
2. Add a file without copying it locally:
   ```bash
   git annex addurl file:///path/to/file --file=relative/path/in/repo
   ```
3. Add external hard drives as remotes:
   ```bash
   git annex initremote <remote-name> type=directory directory=/path/to/drive encryption=none
   ```
4. Set redundancy:
   ```bash
   git annex numcopies 2
   ```
5. Copy files to remotes:
   ```bash
   git annex copy <file> --to=<remote-name>
   ```
6. Verify file locations:
   ```bash
   git annex whereis <file>
   ```

By following these steps, you can efficiently manage large files with `git-annex` and ensure redundancy across multiple external hard drives.