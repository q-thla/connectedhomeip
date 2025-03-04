# Copyright (c) 2021 Project CHIP Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import logging
import os
import shutil
import tarfile
from abc import ABC, abstractmethod


class Builder(ABC):
    """Generic builder base class for CHIP.

    Provides ability to boostrap and copy output artifacts and subclasses can use
    a generic shell runner.

    """

    def __init__(self, root, runner, output_prefix: str = 'out'):
        self.root = os.path.abspath(root)
        self._runner = runner
        self.output_prefix = output_prefix
        self._enable_flashbundle = False

        # Set post-init once actual build target is known
        self.identifier = None
        self.output_dir = None

    def enable_flashbundle(self, enable_flashbundle: bool):
        self._enable_flashbundle = enable_flashbundle

    @abstractmethod
    def generate(self):
        """Generate the build files - generally the ninja/makefiles"""
        raise NotImplementedError()

    @abstractmethod
    def _build(self):
        """Perform an actual build"""
        raise NotImplementedError()

    def _generate_flashbundle(self):
        """Perform an actual generating of flashbundle

           May do nothing (and builder can choose not to implement this) if the
           app does not need special steps for generating flashbundle. (e.g. the
           example apps on Linux platform can run the ELF files directly.)
        """
        pass

    @abstractmethod
    def build_outputs(self):
        """Return a list of relevant output files after a build.

           May use build output data (e.g. manifests), so this should be invoked
           only after a build has succeeded.
        """
        raise NotImplementedError()

    def flashbundle(self):
        """Return the files in flashbundle.

           Return an empty dict (and builder can choose not to implement this) if the
           app does not need special files as flashbundle. (e.g. the example apps on
           Linux platform can run the ELF files directly.)

           May use data from do_generate_flashbundle, so this should be invoked only
           after do_generate_flashbundle has succeeded.
        """
        return {}

    def outputs(self):
        artifacts = self.build_outputs()
        if self._enable_flashbundle:
            artifacts.update(self.flashbundle())
        return artifacts

    def build(self):
        self._build()
        if self._enable_flashbundle:
            self._generate_flashbundle()

    def _Execute(self, cmdarray, cwd=None, title=None):
        self._runner.Run(cmdarray, cwd=cwd, title=title)

    def CompressArtifacts(self, target_file: str):
        with tarfile.open(target_file, "w:gz") as tar:
            for target_name, source_name in self.outputs().items():
                logging.info(
                    f'Adding {source_name} into {target_file}/{target_name}')
                tar.add(source_name, target_name)

    def CopyArtifacts(self, target_dir: str):
        for target_name, source_name in self.outputs().items():
            target_full_name = os.path.join(target_dir, target_name)

            logging.info('Copying %s into %s', source_name, target_name)

            target_dir_full_name = os.path.dirname(target_full_name)

            if not os.path.exists(target_dir_full_name):
                logging.info('Creating subdirectory %s first',
                             target_dir_full_name)
                os.makedirs(target_dir_full_name)

            shutil.copyfile(source_name, target_full_name)
            shutil.copymode(source_name, target_full_name)

    def SetIdentifier(self, platform: str, board: str, app: str, enable_rpcs: bool = False):
        self.identifier = '-'.join([platform, board, app])
        if enable_rpcs:
            self.identifier = self.identifier + "-rpc"
        self.output_dir = os.path.join(self.output_prefix, self.identifier)
